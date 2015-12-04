#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct msg{
	long type;
	char name[20];
	int age;
	float score;
}msg;

int main() {
	int id = msgget(0x9999, 0);		//纯取得消息队列
	if(id == -1) {
		perror("msgget");
		return -1;
	}

	long type;
	msg m;
	printf("请输入想收取的消息类型（0表示随意）:");
	scanf("%ld", &type);

	if(msgrcv(id, &m, sizeof(m) - sizeof(long), type, IPC_NOWAIT) < 0) {
		puts("没有类型的消息\n");
	}else {
		printf("类型：%ld\n姓名：%s\n年龄：%d\n成绩：%f\n",
			m.type, m.name, m.age, m.score);
	}
	return 0;
}
