#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

#define SHMSIZE 500

pid_t myfork(unsigned char* p, unsigned char d, int semid)
{
	pid_t pid = fork();
	if ( pid==0 )
	{
		int i;
		struct sembuf sembuffer;
		for(;;)
		{
			sembuffer.sem_num = 0;           // 何番目のセマフォに対してアクセス権を要求するか指定します。
			sembuffer.sem_op = -1;           //  
			sembuffer.sem_flg = SEM_UNDO;    // OSはプロセスが行ったsemvalへの捜査を覚えていて、プロセスが終了した際にsemvalの値を元に戻す
			semop(semid, &sembuffer, 1);

			for( i=0 ; i<SHMSIZE; ++i )
				p[i] = d;

			sembuffer.sem_num = 0;
			sembuffer.sem_op = 1;           // 処理が終わったら1を設定する(先ほどは-1であることに注意)
			sembuffer.sem_flg = SEM_UNDO;
			semop(semid, &sembuffer, 1);
		}
		assert(0);
	}
	return pid;
}

int main(int argc, char** argv)
{
	int segment;
	unsigned char *p;
	pid_t c1,c2,c3,c4,c5;
	int j;
	int status;
	int semid;

	segment = shmget(IPC_PRIVATE, SHMSIZE, S_IRUSR|S_IWUSR);
	p = (unsigned char*)shmat (segment, NULL, 0);

	semid = semget(IPC_PRIVATE, 1, S_IRUSR|S_IWUSR);
	if ( semid == -1 )
		exit(1);

	if ( semctl(semid, 0, SETVAL, 1) != 0 )
		exit(0);

	c1 = myfork(p,0x00,semid);
	c2 = myfork(p,0xAA,semid);
	c3 = myfork(p,0xBB,semid);
	c4 = myfork(p,0xCC,semid);
	c5 = myfork(p,0xDD,semid);

	for ( j=0 ; j < 100000 ; ++j )
	{
		int k;
		unsigned char d;
		struct sembuf sembuffer;

		sembuffer.sem_num = 0;
		sembuffer.sem_op = -1;
		sembuffer.sem_flg = SEM_UNDO;
		semop(semid, &sembuffer, 1);

		d = p[0];
		for ( k=0 ; k < SHMSIZE; ++k  )
		{
			if( d != p[k] )
			{
	printf("error: p[0]!=p[%d] (0x%02X!=0x%02X)\n", k, d, p[k]);
				break;
			}
		}
		fflush(stdout);

		sembuffer.sem_num = 0;
		sembuffer.sem_op = 1;
		sembuffer.sem_flg = SEM_UNDO;
		semop(semid, &sembuffer, 1);
	}

	kill(c1, SIGTERM);
	kill(c2, SIGTERM);
	kill(c3, SIGTERM);
	kill(c4, SIGTERM);
	kill(c5, SIGTERM);

	wait(&status);
	wait(&status);
	wait(&status);
	wait(&status);
	wait(&status);
	
	semctl (semid, 0, IPC_RMID);
	shmctl (segment, IPC_RMID, NULL);
	return 0;
}

