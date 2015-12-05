/* 
 *	信号量级的简单实用 
 *  首先创建一个值为5的信号量级，在创建10个进程，这10个进程只有5个进程可以同时工作
 *  每有一个进程开始工作，信号量的值就减去1，每当有一个进程工作完毕，信号量的值则、
 *  自动回复（+1）；
 *  注意：只有在对信号量+1/-1操作是将sb.sem_flg设置为SEM_UNDO时，在进程结束后信号量
 *  的值才会自动回复。
*/
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SEM_KEY 0X8888

int main() {
	int id = semget(SEM_KEY, 1, IPC_CREAT|0600);//打开或创建信号量级
	if(id == -1) {
		perror("semget");
		return -1;
	}

	semctl(id, 0, SETVAL, 5);	//设置信号量值

	int i = 0;
	for(i = 0; i < 10; i++) {
		if(fork() == 0) {
			struct sembuf sb;
			sb.sem_num = 0;		//信号量下标
			sb.sem_op = 1;		//加一减一操作（减一）
			sb.sem_flg = SEM_UNDO;	//进程结束后回复信号量值
	
			while(semop(id, &sb, 1) == -1) {
				;
			}

			srand(getpid());	//随机数种子
			printf("%d进程开始工作\n", getpid());
			sleep(rand() % 20);
			printf("%d进程工作完毕\n", getpid());

			sb.sem_op = +1;
			semop(id, &sb, 1);

			exit(0);
		}
	}
	/* 等待所有子进程结束 */
	while(wait(NULL) != -1);

	semctl(id, 0, IPC_RMID, NULL);	//删除信号量集
	puts("全部子进程结束\n");

	return 0;
}
