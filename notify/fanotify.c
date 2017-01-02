/*
 * fanotifyを使ってマウントポイントに関するファイルの変更があれば通知する。
 * fanotify_init, fanotify_markなどのシステムコールを利用している。
 *
 * [使い方]
 * a.outの後にマウントポイントを指定する。以下ではルート(/)を指定している。
 * 終了するにはコンソールからエンターを押下すれば正常終了する。
 * $ sudo ./a.out /
 * Press enter key to terminate.
 * Listening for events.
 * FAN_OPEN_PERM: File /etc/localtime
 * FAN_OPEN_PERM: File /etc/localtime
 * FAN_OPEN_PERM: File /etc/fstab
 * FAN_OPEN_PERM: File /etc/localtime
 * FAN_OPEN_PERM: File /etc/localtime
 * FAN_OPEN_PERM: File /etc/localtime
 * FAN_OPEN_PERM: File /etc/localtime
 * (snip)
 *
 *
 */
#define _GNU_SOURCE     /* O_LARGEFILE の定義を得るために必要 */
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fanotify.h>
#include <unistd.h>

/* ファイルディスクリプター 'fd' から読み出しできる全 fanotify イベントを読み出す */
static void handle_events(int fd) {

    const struct fanotify_event_metadata *metadata;
    struct fanotify_event_metadata buf[200];
    ssize_t len;
    char path[PATH_MAX];
    ssize_t path_len;
    char procfd_path[PATH_MAX];
    struct fanotify_response response;

    /* fanotify ファイルディスクリプターからイベントが読み出せる間はループする */
    for(;;) {

        /* イベントを読み出す */
        len = read(fd, (void *) &buf, sizeof(buf));
        if (len == -1 && errno != EAGAIN) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        /* 読み出せるデータの最後に達しているかチェックする */
        if (len <= 0)
            break;

        /* バッファーの最初のイベントを参照する */
        metadata = buf;

        /* バッファー内の全イベントを処理する */
        while (FAN_EVENT_OK(metadata, len)) {

            /* 実行時とコンパイル時の構造体が一致するか確認する */
            if (metadata->vers != FANOTIFY_METADATA_VERSION) {
                fprintf(stderr,
                        "Mismatch of fanotify metadata version.\n");
                exit(EXIT_FAILURE);
            }

            /* metadata->fd には、キューのオーバーフローを示す FAN_NOFD か、
               ファイルディスクリプター (負でない整数) のいずれかが入っている。
               ここではキューのオーバーフローは無視している。 */
            if (metadata->fd >= 0) {

                /* オープン許可イベントを処理する */
                if (metadata->mask & FAN_OPEN_PERM) {
                    printf("FAN_OPEN_PERM: ");

                    /* ファイルのオープンを許可する */
                    response.fd = metadata->fd;
                    response.response = FAN_ALLOW;
                    write(fd, &response,
                          sizeof(struct fanotify_response));
                }

                /* 書き込み可能ファイルのクローズイベントを処理する */
                if (metadata->mask & FAN_CLOSE_WRITE)
                    printf("FAN_CLOSE_WRITE: ");

                /* アクセスされたファイルのパス名を取得し表示する */
                snprintf(procfd_path, sizeof(procfd_path), "/proc/self/fd/%d", metadata->fd);
                path_len = readlink(procfd_path, path, sizeof(path) - 1);
                if (path_len == -1) {
                    perror("readlink");
                    exit(EXIT_FAILURE);
                }

                path[path_len] = '\0';
                printf("File %s\n", path);

                /* イベントのファイルディスクリプターをクローズする */
                close(metadata->fd);
            }

            /* 次のイベントに進む */
            metadata = FAN_EVENT_NEXT(metadata, len);
        }
    }
}

int main(int argc, char *argv[]) {
    char buf;
    int fd, poll_num;
    nfds_t nfds;
    struct pollfd fds[2];

    /* マウントポイントが指定されたか確認する */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s MOUNT\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Press enter key to terminate.\n");

    /* fanotify API にアクセスするためのファイルディスクリプターを作成する */
    fd = fanotify_init(FAN_CLOEXEC | FAN_CLASS_CONTENT | FAN_NONBLOCK, O_RDONLY | O_LARGEFILE);
    if (fd == -1) {
        perror("fanotify_init");
        exit(EXIT_FAILURE);
    }

    /* 指定されたマウントに対して以下を監視するようにマークを付ける:
       - ファイルのオープン前のアクセス許可イベント
       - 書き込み可能なファイルディスクリプターのクローズ後の
         通知イベント */
    if (fanotify_mark(fd, FAN_MARK_ADD | FAN_MARK_MOUNT,
                      FAN_OPEN_PERM | FAN_CLOSE_WRITE, AT_FDCWD,
                      argv[1]) == -1) {
        perror("fanotify_mark");
        exit(EXIT_FAILURE);
    }

    /* ポーリングの準備(コンソール入力とfanotifyからの入力音２つ */
    nfds = 2;

    /* コンソールの入力 */
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    /* fanotify の入力 */
    fds[1].fd = fd;
    fds[1].events = POLLIN;

    /* イベントの発生を待つループ */
    printf("Listening for events.\n");
    while (1) {
        poll_num = poll(fds, nfds, -1);
        if (poll_num == -1) {
            if (errno == EINTR)     /* シグナルに割り込まれた場合 */
                continue;           /* poll() を再開する */

            perror("poll");         /* 予期しないエラー */
            exit(EXIT_FAILURE);
        }

        if (poll_num > 0) {

			// コンソール上から改行入力があればwhileループから抜けて処理を終了する。
            if (fds[0].revents & POLLIN) {
                /* コンソールからの入力がある場合: 空の標準入力であれば終了 */
                while (read(STDIN_FILENO, &buf, 1) > 0 && buf != '\n')
                    continue;
                break;
            }

            if (fds[1].revents & POLLIN) {
                /* fanotify イベントがある場合 */
                handle_events(fd);
            }
        }
    }

    printf("Listening for events stopped.\n");
    exit(EXIT_SUCCESS);
}
