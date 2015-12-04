/* 子进程发送一个带参信号，父进程接收并处理这个带参信号 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void func(int sig, siginfo_t *info, void *p) {
	printf("收到信号，来自用户%d的进程%d，附带参数为%d\n", info->si_uid,
		info->si_pid, info->si_value.sival_int);
}

int main() {
	struct sigaction act, oldact;

	act.sa_sigaction = func;	//设置带参信号处理函数
	sigemptyset(&act.sa_mask);	//不用屏蔽什么信号
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &act, &oldact);	//登记信号处理

	if(fork() ==0) {
		union sigval v;
		printf("uid=%d, pid=%d\n", getuid(), getpid());
		v.sival_int = 2013;	//设置要传递的参数
		sigqueue(getppid(), SIGUSR2, v);//发送信号和参数
		sleep(1);
	}else {
		pause();
	}
	return 0;
}
