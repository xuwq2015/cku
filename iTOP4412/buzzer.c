/* 
	argv[1]=0时，蜂鸣器不想，=1时想；
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <error.h>

#define BUZZER_C 2

int main(int argc, char *argv[]) {
	int fd, ret, buzzer_c;
	char *buzzer_ctl = "/dev/buzzer_ctl";

	buzzer_c = BUZZER_C;

	if(argc >= 2) {
		printf("cmd error\n");
		exit(1);
	}

	if(atoi(argv[1]) >= buzzer_c) {
		printf("argv[1] is 0 or 1\n");
		exit(1);
	}

	if((fd = open(buzzer_ctl, O_RDWR|O_NOCTTY|O_NDELAY)) < 0) {
		perror("open");
		exit(1);
	}
	
	if((ret = ioctl(fd, atoi(argv[1]), 0)) < 0) {
		perror("ioctl");
		exit(1);
	}
	close(fd);
	return 0;
}
