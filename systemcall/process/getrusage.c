/*
 * 資源の使用量を取得するプログラム
 *  REF: http://linuxjm.sourceforge.jp/html/LDP_man-pages/man2/getrusage.2.html
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

static void
dummy(void)
{
    int cnt = 0;
    int sum = 1;

    for(cnt = 0; cnt <= 1000000; cnt++ ){
        sum *= cnt;
    }
}

int
main(void)
{
    struct rusage usage;
    int rc = 0;
    dummy();
	
	/* getrusageの第１引数には下記３つが指定できる。usageはポインタ経由で情報を取得する
	 *   RUSAGE_SELF:     呼び出したプロセスの資源使用量、 そのプロセス内の全スレッドが使用している資源の合計を返す。
	 *   RUSAGE_CHILDREN: 呼び出したプロセスの子プロセスのうち、 終了して待ち状態にある全プロセスが使用している資源使用量の統計を返す。
	 *   RUSAGE_THREAD:   呼び出したスレッドに関する資源使用量の統計を返す。(Linux 2.6.26 以降)
	 */
    rc = getrusage(RUSAGE_SELF, &usage);
    if(rc < 0){
        printf("Error: getrusage(%d) %s\n", errno, strerror(errno));
        return(-1);
    }

    printf("usr time    = %ld.%d\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);  // 使用されたユーザCPU時間
    printf("sys time    = %ld.%d\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);  // 使用されたシステムCPU時間

    printf("ru_maxrss   = %ld\n", usage.ru_maxrss);                                   // RAM上に存在する仮想ページのサイズ(resident set size)の最大値
    printf("ru_ixrss    = %ld\n", usage.ru_ixrss);                                    // 共有メモリの合計サイズ
    printf("ru_idrss    = %ld\n", usage.ru_idrss);                                    // 非共有データの合計サイズ
    printf("ru_isrss    = %ld\n", usage.ru_isrss);                                    // 非共有スタックの合計サイズ

    printf("ru_minflt   = %ld\n", usage.ru_minflt);                                    // ページの再利用 (ソフトページフォルト)
    printf("ru_majflt   = %ld\n", usage.ru_majflt);                                   // ページフォールト (ハードページフォルト)
    printf("ru_nswap    = %ld\n", usage.ru_nswap);                                    // スワップ

    printf("ru_inblock  = %ld\n", usage.ru_inblock);                                  // ブロック入力操作
    printf("ru_oublock  = %ld\n", usage.ru_oublock);                                  // ブロック出力操作

    printf("ru_msgsnd   = %ld\n", usage.ru_msgsnd);                                   // 送信された IPC メッセージ
    printf("ru_msgrcv   = %ld\n", usage.ru_msgrcv);                                   // 受信された IPC メッセージ
    printf("ru_nsignals = %ld\n", usage.ru_nsignals);                                 // 受信されたシグナル

    printf("ru_nvcsw    = %ld\n", usage.ru_nvcsw);                                    // 意図したコンテキスト切り替え
    printf("ru_nivcsw   = %ld\n", usage.ru_nivcsw);                                   // 意図しないコンテキスト切り替え

    return(0);
}
