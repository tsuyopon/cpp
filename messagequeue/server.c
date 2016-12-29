#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

main()
{
    int msqid;
    key_t msgkey;
    struct msgbuf{
        long mtype;
        char mdata[256];
    };
    struct msgbuf msgdata,*p;

    p = &msgdata;
    msgkey = ftok("mrecv",'a');
    msqid = msgget(msgkey,IPC_CREAT|0666);
    while(1)
    {
        msgrcv(msqid,p,sizeof(p->mdata),0,0);
        printf("message received from %ld\n%s\n",p->mtype,p->mdata);
    }
}
