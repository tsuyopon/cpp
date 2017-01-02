/*
 * 概要:
 * inotify APIを使ってファイルやディレクトリの変更を監視するプログラム
 *
 * [使い方]
 * a.outの引数としてファイルやディレクトリを複数指定します。
 * $ ./a.out  /path/to/file_or_dir [...]
 *
 * 以下にサンプルを示す。inotifyで監視したいファイルやディレクトリを指定する。
 * 終了したい場合には、エンターなどの改行を入力すればOK
 * $ ./a.out  /tmp/hoge 
 * Press ENTER key to terminate.
 * Listening for events.
 * (ここで$ echo "aaa" >> /tmp/hoge を実行すると以下が出力される)
 * IN_OPEN: /tmp/hoge/ [file]
 * IN_CLOSE_WRITE: /tmp/hoge/ [file]
 * (ここでエンターを入力するとプログラムが終了する)  
 * Listening for events stopped.
 *
 * 参考元: https://linuxjm.osdn.jp/html/LDP_man-pages/man7/inotify.7.html
 */
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>

/* Read all available inotify events from the file descriptor 'fd'.
   wd is the table of watch descriptors for the directories in argv.
   argc is the length of wd and argv.
   argv is the list of watched directories.
   Entry 0 of wd and argv is unused. */
static void
handle_events(int fd, int *wd, int argc, char* argv[])
{
    /* Some systems cannot read integer variables if they are not
       properly aligned. On other systems, incorrect alignment may
       decrease performance. Hence, the buffer used for reading from
       the inotify file descriptor should have the same alignment as
       struct inotify_event. */

    char buf[4096]
        __attribute__ ((aligned(__alignof__(struct inotify_event))));
    const struct inotify_event *event;
    int i;
    ssize_t len;
    char *ptr;

    /* Loop while events can be read from inotify file descriptor. */
    for (;;) {

        /* Read some events. */
        len = read(fd, buf, sizeof buf);
        if (len == -1 && errno != EAGAIN) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        /* If the nonblocking read() found no events to read, then
           it returns -1 with errno set to EAGAIN. In that case,
           we exit the loop. */
        if (len <= 0)
            break;

        /* バッファー内の全イベントを処理する */
        for (ptr = buf; ptr < buf + len; ptr += sizeof(struct inotify_event) + event->len) {

            event = (const struct inotify_event *) ptr;

            /* Print event type */
            if (event->mask & IN_OPEN)
                printf("IN_OPEN: ");
            if (event->mask & IN_CLOSE_NOWRITE)
                printf("IN_CLOSE_NOWRITE: ");
            if (event->mask & IN_CLOSE_WRITE)
                printf("IN_CLOSE_WRITE: ");

            /* Print the name of the watched directory */
            for (i = 1; i < argc; ++i) {
                if (wd[i] == event->wd) {
                    printf("%s/", argv[i]);
                    break;
                }
            }

            /* Print the name of the file */
            if (event->len)
                printf("%s", event->name);

            /* Print type of filesystem object */
            if (event->mask & IN_ISDIR)
                printf(" [directory]\n");
            else
                printf(" [file]\n");
        }
    }
}

int
main(int argc, char* argv[])
{
    char buf;
    int fd, i, poll_num;
    int *wd;
    nfds_t nfds;
    struct pollfd fds[2];

	// 引数としてファイルやディレクトリを1つ以上指定する必要がある
    if (argc < 2) {
        printf("Usage: %s PATH [PATH ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Press ENTER key to terminate.\n");

	// inotifyインスタンスの初期化を行う。inotify_initとinotify_init1というシステムコールがあり、後者の方がフラグで様々な機能を持つ
    fd = inotify_init1(IN_NONBLOCK);
    if (fd == -1) {
        perror("inotify_init1");
        exit(EXIT_FAILURE);
    }

    /* Allocate memory for watch descriptors */
    wd = calloc(argc, sizeof(int));
    if (wd == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    /* Mark directories for events
       - file was opened
       - file was closed */
    for (i = 1; i < argc; i++) {
		// 監視対象のファイルやディレクトリを追加する。削除する場合にはinotify_rm_watchを使う
        wd[i] = inotify_add_watch(fd, argv[i], IN_OPEN | IN_CLOSE);
        if (wd[i] == -1) {
            fprintf(stderr, "Cannot watch '%s'\n", argv[i]);
            perror("inotify_add_watch");
            exit(EXIT_FAILURE);
        }
    }

    /* ポーリングの準備(2というのは次のコンソール入力とinotify入力の監視 */
    nfds = 2;

    /* コンソールの入力 */
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    /* Inotify input */
    fds[1].fd = fd;
    fds[1].events = POLLIN;

    /* Wait for events and/or terminal input */
    printf("Listening for events.\n");
    while (1) {
        poll_num = poll(fds, nfds, -1);
        if (poll_num == -1) {
            if (errno == EINTR)
                continue;
            perror("poll");
            exit(EXIT_FAILURE);
        }

        if (poll_num > 0) {

			// コンソール上から何か入力されたらwhileループを終了する。
            if (fds[0].revents & POLLIN) {
                /* Console input is available. Empty stdin and quit */
                while (read(STDIN_FILENO, &buf, 1) > 0 && buf != '\n')
                    continue;
                break;
            }

			// inotifyで何か検知されたらhandle_eventsを呼び出す
            if (fds[1].revents & POLLIN) {
                /* Inotify events are available */
                handle_events(fd, wd, argc, argv);
            }
        }
    }

    printf("Listening for events stopped.\n");

    /* Close inotify file descriptor */
    close(fd);

    free(wd);
    exit(EXIT_SUCCESS);
}
