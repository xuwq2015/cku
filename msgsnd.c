#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

typedef struct msg {
	long type;
	char name[20];
	int age;
	float score;
}msg;

int main() {
	int id = msgget(0x9999, IPC_CREAT|0600);
	printf("id=%d\n", id);
	if(id == -1) {
		perror("msgget");
		return -1;
	}

	msg m;

	printf("请输入类型、姓名、年龄和成绩\n");
	scanf("%ld%s%d%f", &m.type, m.name, &m.age, &m.score);

	msgsnd(id, &m, sizeof(m) - sizeof(long), 0);

	return 0;
}
