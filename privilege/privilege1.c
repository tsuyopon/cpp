/*
 * root権限で実行して「$ sudo ./a.out」、一時的にnobodyへと実行権限を落とし、またrootに権限昇格させるプログラム
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

void drop_privileges(uid_t new_uid, gid_t new_gid) {
    if (setegid(new_gid) != 0) {
        perror("Failed to set effective group ID");
        exit(EXIT_FAILURE);
    }

    if (seteuid(new_uid) != 0) {
        perror("Failed to set effective user ID");
        exit(EXIT_FAILURE);
    }
}

void regain_privileges(uid_t original_uid, gid_t original_gid) {

    // 保存しておいた本来のuid、gidに実行UID、実行GIDをセットする

    if (seteuid(original_uid) != 0) {
        perror("Failed to regain effective user ID");
        exit(EXIT_FAILURE);
    }

    if (setegid(original_gid) != 0) {
        perror("Failed to regain effective group ID");
        exit(EXIT_FAILURE);
    }
}

int main() {

    uid_t original_uid = geteuid(); // 保存されたセットユーザーID
    gid_t original_gid = getegid(); // 保存されたセットグループID

    // 実行対象のユーザー（例: 非特権ユーザー "nobody"）
    struct passwd *pwd = getpwnam("nobody");
    if (pwd == NULL) {
        perror("Failed to find user 'nobody'");
        exit(EXIT_FAILURE);
    }

    printf("Original UID: %d, GID: %d\n", original_uid, original_gid);
    printf("Switching to user: %s (UID: %d, GID: %d)\n", pwd->pw_name, pwd->pw_uid, pwd->pw_gid);

    // 権限を落とす
    drop_privileges(pwd->pw_uid, pwd->pw_gid);
    printf("Privileges dropped. Current UID: %d, GID: %d\n", geteuid(), getegid());

    // 権限が落ちた状態で動作
    printf("Running as 'nobody'.\n");

    // 権限を再び上げる
    regain_privileges(original_uid, original_gid);
    printf("Privileges regained. Current UID: %d, GID: %d\n", geteuid(), getegid());

    printf("Running as root again.\n");

    return 0;
}

