#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

char chop(char *);

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
    printf("Enter message: ");
    fflush(stdin);
    fgets(p->mdata,BUFSIZ,stdin);
    chop(p->mdata);
    p->mtype = getpid();
    msgkey = ftok("mrecv",'a');
    msqid = msgget(msgkey,IPC_CREAT|0666);
    msgsnd(msqid,p,sizeof(p->mdata),0);
}

char chop(char *s)
{
    char c;
    int i;

    for( i = 0 ; i < 256 ; i++ )
    {
        if( s[i] == '\0' && i > 0 )
        {
            c = s[i-1];
            s[i-1] = '\0';
            return(c);
        }
    }
    return('\0');
}
