#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(int argc, char *argv[])
{
	int id;
	char *adr;

	if(argc <= 2){
		fprintf(stderr, "Usage: shm_writer shm_id string\n");
		exit(EXIT_FAILURE);
	}

	id = atoi(argv[1]);

	// shmatにより自プロセスのデータセグメントにマップ(アタッチ)する (Shared Memory Segment Attach)
	if( (adr = (char*)shmat(id,0,0)) == (void*)-1){
		perror("shmat error");
	} else {
		strcpy(adr, argv[2]);
		fprintf(stderr, "written\n");
		// 共有メモリをアンマップ(でタッチ)する。 (Shared Memory Segment Detach)
		if(shmdt(adr) == -1){
			perror("shmdt error");
		}
	}
}
