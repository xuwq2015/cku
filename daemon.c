/*
 *	创建一个守护进程，只需调用daemon函数即可。
 *	自己创建守护进程的一般步骤：
 *	1、fork()让父进程结束
 *	2、关闭终端相关的三个文件
 *	3、重新设置当前目录(一般设置为跟目录或者主目录
 *	4、重设umask
 *	5、setsid()独立建一个进程组（和一个会话）
 *	6、无限循环在后台工作
*/
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <pwd.h>

int main() {
	daemon(0, 0);	//把进程设为守护进程
	
	//getpwuid(getuid())->pw_dir为获取主目录
	chdir(getpwuid(getuid())->pw_dir);

	char c = 'A';
	while(1) {
		int fd = open("letter", O_RDWR|O_CREAT, 0755);
		if(fd == -1) {
			perror("open");
			return -1;
		}
		read(fd, &c, 1);	
		++c;
		if(c > 'Z')
			c = 'A';
		lseek(fd, 0, SEEK_SET);
		write(fd, &c, 1);
		close(fd);
		sleep(1);
	}
	return 0;
}
