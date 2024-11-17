/*
 * seteuidを変更することによって、initgroupシステムコールが失敗することを確かめる
 * 
 * // initgroupシステムコールが成功する場合
 * $ gcc -DSUCCESS_INITGROUPS initgroup1.c
 * [~/git/cpp/privilege]$ sudo ./a.out 
 * Current UID: 0, GID: 0
 * Current Effective UID: 0, GID: 0
 * Switching to user: _www (UID: 70, GID: 70)
 * Privileges dropped. Effective UID: 0, GID: 0
 * Privileges regained. Effective UID: 0, GID: 0
 * 
 * 
 * // initgroupシステムコールが失敗する場合
 * $ gcc initgroup1.c
 * $ sudo ./a.out 
 * Current UID: 0, GID: 0
 * Current Effective UID: 0, GID: 0
 * Switching to user: _www (UID: 70, GID: 70)
 * Privileges dropped. Effective UID: 70, GID: 0
 * initgroups failed: Operation not permitted
 * Remaining UID: 0, GID: 0
 * Effective UID: 70, GID: 0
 * Privileges regained. Effective UID: 0, GID: 0
 * 
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

void impersonate(const struct passwd *pwd) {
    printf("Switching to user: %s (UID: %d, GID: %d)\n", pwd->pw_name, pwd->pw_uid, pwd->pw_gid);

    // Step 1: Drop privileges temporarily using seteuid and setegid
    if (seteuid(pwd->pw_uid) != 0) {
        perror("Failed to set effective UID");
        return;
    }

// 一度手前で別のアカウント(www)にEffective UIDを変更してしまったので、そのままinitgroupsを実行すると失敗する
// そのため、下記を有効にすることでrootのEffective UIDと設定変更することで、initgroupsシステムコールが成功するようになる。これを有効にしないとinitgroupsが失敗する。
#ifdef SUCCESS_INITGROUPS
    // Set Root Effective UID
    seteuid(0);
#endif

    printf("Privileges dropped. Effective UID: %d, GID: %d\n", geteuid(), getegid());

    // Step 2: Attempt to initialize supplementary groups (intentionally fail)
    if (initgroups("invalid_user", -1) != 0) { // Provide invalid arguments to fail intentionally
        perror("initgroups failed");
        printf("Remaining UID: %d, GID: %d\n", getuid(), getgid());
        printf("Effective UID: %d, GID: %d\n", geteuid(), getegid());
    }

    // Step 3: Try to regain original privileges (back to root)
    if (seteuid(0) != 0) {
        perror("Failed to regain effective UID");
    }
    if (setegid(0) != 0) {
        perror("Failed to regain effective GID");
    }
    printf("Privileges regained. Effective UID: %d, GID: %d\n", geteuid(), getegid());
}

int main() {
    struct passwd *pwd = getpwnam("www"); // Use a low-privileged user like 'nobody'
    if (pwd == NULL) {
        perror("Failed to get user info");
        exit(EXIT_FAILURE);
    }

    printf("Current UID: %d, GID: %d\n", getuid(), getgid());
    printf("Current Effective UID: %d, GID: %d\n", geteuid(), getegid());

    impersonate(pwd);

    return 0;
}

