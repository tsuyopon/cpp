#include<stdio.h>

int front, rear;
int myqueue[100];

void init(){
	front = 0;
	rear  = 0;
}

void queue(int x){

	myqueue[rear] = x;
	if(rear == 99){
		rear = 0;
	} else {
		rear++;
	}

}

void deque(int *x){
	printf("%d, %d", front, rear);
	if( front == rear ){
		return;
	}

	int tmp;
	tmp = myqueue[front];
	printf("aaa=%d\n", tmp);
	*x = tmp;
	front++;
	return;
}

int main(){
	int z = 0;
	init();
	queue(3);
	queue(2);
	printf("%d\n", myqueue[0]);
	printf("%d\n", myqueue[1]);
	deque(&z);
	printf("%d\n", z);
}
