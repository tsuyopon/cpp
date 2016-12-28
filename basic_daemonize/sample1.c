/*
 * [使い方]
 * 実行すると即座にプロンプトが帰ってくるので、その後psなどで裏側で動作していることを確認することができます。
 * $ ./a.out
 * $ ps auxww | grep -i a.out 
 *
 * 参考: http://d.hatena.ne.jp/rero/20041002/p1
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>

int main(void)
{
    pid_t pid, sid;

    /* システムロガーへの接続を開始 */
    openlog("testdaemon", LOG_PID, LOG_DAEMON);

    /* 子プロセスの開始 */
    pid = fork();
    if ( pid < 0 ) {
        syslog(LOG_ERR, "fork");
        exit(EXIT_FAILURE);
    }

    /* 親プロセスを終了 */
    if ( pid > 0 ) exit(EXIT_SUCCESS);

    /* 新しいセッションを作成 */
    sid = setsid();
    if ( sid < 0 ) {
        syslog(LOG_ERR, "setsid");
        exit(EXIT_FAILURE);
    }

    /* カレントディレクトリを / に変更 */
    if ( chdir("/") < 0 ) {
        syslog(LOG_ERR, "chdir");
        exit(EXIT_FAILURE);
    }

    /* ファイル作成マスクをリセット */
    umask(0);

    /* 標準入力，標準出力，標準エラー出力を閉じる */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* この daemon でやりたいことをやる */
	while(1){
		printf("hoge");
	}

    /* システムロガーへの接続を終了 */
    closelog();

    exit(EXIT_SUCCESS);
}
