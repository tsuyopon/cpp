#include<stdio.h>
#include<stdlib.h>
#include<string.h>  // strcpy
#include<unistd.h>  // sleep
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(void)
{
	int id;
	char *adr;

	/* IPC_PRIVATEを指定すると、新規にshmが生成されることになる */
	if( (id = shmget(IPC_PRIVATE, 512, IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(-1);
	}

	printf("SharedMemoryID = %d\n", id);

	// char形で取得
	if( (adr = (char*)shmat(id, NULL, 0)) == (void*)-1){
		perror("shmat");
	} else {
		strcpy(adr, "Initial");
		// 1秒ごとに出力
		while(1){
			printf("%s\n", adr);
			// "end"で終了とする
			if(strcmp(adr, "end") == 0){
				break;
			}
			sleep(1);
		}
		if(shmdt(adr) == -1){
			perror("shmdt");
		}
	}

	// shmを終わらせる
	if(shmctl(id, IPC_RMID, 0) == -1){
		perror("shmctl");
		exit(-1);
	}

	return 0;
}
