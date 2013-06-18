/*
 * 
 * <usage>
 *     $ gmake sample1
 *     $ ./a.out
 *     $ redis-cli
 *     redis> get host
 *     "123"
 *
 * See http://6pongi.wordpress.com/2012/08/12/hiredis/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hiredis/hiredis.h"

int main(void) {

        const char *hostname = "localhost";
        const char *id = "123";

        redisContext *c = redisConnect("127.0.0.1", 6379);
        if (c->err) {
                printf("Connect NG: %s\n", c->errstr);
        }else{
                printf("Connect OK  \n");
        }

        redisReply *reply_set;
        reply_set = (redisReply*)redisCommand(c,"set host %s", id);
        if( reply_set == NULL ){
            // This error handling is needed so as not to cause segmentation fault.
            printf("If Redis server could not reply, redisCommand() will return NULL\n");
            redisFree(c);
            exit(0);
        }
        freeReplyObject(reply_set);

        redisReply *reply_host;
        reply_host = (redisReply*)redisCommand(c,"get host");
        if( reply_set == NULL ){
            printf("If Redis server could not reply, redisCommand() will return NULL\n");
            redisFree(c);
            exit(0);
        }

        if (reply_host->type == REDIS_REPLY_STRING) {
            printf("hostid of %s is %s\n", hostname,reply_host->str);
        }
        freeReplyObject(reply_host);

        //  If forgot redisFree(), redis server's file-descripter will be exhausted.
        redisFree(c);

        return 1;
}
