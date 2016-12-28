// gcc <file>.c -I /usr/local/include/zookeeper/ -lzookeeper_mt だとうまくいく(値も取れる)
// gcc <file>.c -I /usr/local/include/zookeeper/ -lzookeeper_sst だとうまくいかない(値も取れないし、zookeeper_closeでセグフォ)
#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>

void watcher(zhandle_t *zzh, int32_t type, int32_t state, const char *path, void *watcherCtx){}

int32_t main(int argc, char* argv[]){
    zoo_set_debug_level(ZOO_LOG_LEVEL_INFO);
    zhandle_t *zh = zookeeper_init("localhost:2181", watcher, 10000, 0, 0, 0);
    char buffer[512];
    if(!zh) {
        return errno;
    }

    int32_t rc = zoo_create(zh, "/zk_test", "value", 5, &ZOO_OPEN_ACL_UNSAFE,  
                            ZOO_EPHEMERAL, buffer, sizeof(buffer) - 1); 
    int buflen = sizeof(buffer);
    struct Stat stat;
    rc = zoo_get(zh, "/zk_test", 0, buffer, &buflen, &stat);
    if(rc) {
        printf("error\n");
    } else {
        buffer[buflen]='\0';
        printf("%s\n", buffer);
        printf("version %d\n", stat.version);
    }
    
    sleep(1);
    zookeeper_close(zh);
    return 0;
}

