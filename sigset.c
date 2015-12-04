#include <signal.h>
#include <stdio.h>

int main() {
	sigset_t ss;	//定义一个信号集

	sigemptyset(&ss);	//清空信号集
	//sigfillset(&ss),填充信号集

	puts(sigismember(&ss, SIGINT) ? "sigint" : "noint");
	puts(sigismember(&ss, SIGTERM) ? "sigterm" : "noterm");

	sleep(5);

	sigaddset(&ss, SIGINT);
	sigaddset(&ss, SIGTERM);

	puts(sigismember(&ss, SIGINT) ? "sigint" : "noint");
	puts(sigismember(&ss, SIGTERM) ? "sigterm" : "noterm");

	sleep(5);

	sigdelset(&ss, SIGINT);

	puts(sigismember(&ss, SIGINT) ? "sigint" : "noint");
	puts(sigismember(&ss, SIGTERM) ? "sigterm" : "noterm");

	sleep(5);

	sigfillset(&ss);

	puts(sigismember(&ss, SIGINT) ? "sigint" : "noint");
	puts(sigismember(&ss, SIGTERM) ? "sigterm" : "noterm");
	return 0;
}
