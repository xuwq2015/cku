/* 获取终端的行数和列数 */
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main() {
	struct winsize w;
	for(;;) {
		ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
		printf("%d行, %d列\n", w.ws_row, w.ws_col);
		sleep(1);
	}
	return 0;
}
