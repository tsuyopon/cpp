/*
 * ビルド方法
 *    1. $ sudo apt-get install libcap-dev
 *    2. gcc -lcap xxxx.c
 * 
 * 使い方 
 *    以下の3つのプロセス実行によるケーパビリティ挙動の違いを確認してみてください、
 *    1. ./a.out
 *    2. sudo ./a.out
 *    3. sudo setcap 'cap_net_raw=+ep' a.out ; ./a.out
 * 
 */
#define _GNU_SOURCE
#include <sys/capability.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    cap_t caps = cap_get_proc(); // 現在のケーパビリティ取得
    if (!caps) {
        perror("cap_get_proc");
        return 1;
    }

    // ケーパビリティをテキスト形式に変換
    char *caps_text = cap_to_text(caps, NULL);
    if (caps_text == NULL) {
        perror("cap_to_text failed");
        cap_free(caps);
        exit(EXIT_FAILURE);
    }

    // root権限で実行させた時と、非特権権限で実行させた場合に結果が異なる
    // また、「$ sudo setcap 'cap_net_raw=+ep' a.out 」として実行した場合には権限が付与される
    printf("caps_to_text() returned \"%s\"\n", caps_text);

    // CAP_NET_RAW を追加(複数追加も可能)
    cap_value_t cap_list[1] = {CAP_NET_RAW};
    if (cap_set_flag(caps, CAP_EFFECTIVE, 1, cap_list, CAP_SET) == -1) {
        // 権限がなければここでエラーになる
        perror("cap_set_flag");
        cap_free(caps);
        return 1;
    }

    if (cap_set_proc(caps) == -1) {
        perror("cap_set_proc");
        cap_free(caps);
        return 1;
    }

    printf("CAP_NET_RAW added\n");
    cap_free(caps);

    // プログラムロジックをここに追加
    printf("waiting 5 seconds\n");
    sleep(5); // デバッグ用

    return 0;
}

