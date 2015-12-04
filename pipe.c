#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>


int main() {
	int fd[2];
	pipe(fd);
	char buf[100];

	if(fork() == 0) {//子进程
		close(fd[1]);	//关闭写端保留读端

		int n;

		while((n = read(fd[0], buf, sizeof(buf))) > 0) {	//从管道读取数据
			int i;
			for(i = 0; i < n; i++) {
				if(islower(buf[i])) {
					putchar(toupper(buf[i]));
				}else if(isupper(buf[i])) {
					putchar(tolower(buf[i]));
				}else {
					putchar(buf[i]);
				}
			}
		}
		close(fd[0]);	
	}else {//父进程
		close(fd[0]);	//关闭读端保留写端	
		int n;
		for(;;) {
			n = read(STDIN_FILENO, buf, sizeof(buf));
			if(buf[0] == 'q') {
				break;
			}
			write(fd[1], buf, n);
		}
		close(fd[1]);
	}
	return 0;
}
