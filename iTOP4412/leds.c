/* led等操作 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define LED_NUM 2
#define LED_C 2

//cmd 为0，则灭，1则亮;io为0则是靠近蜂鸣器，为1则靠近按键的小灯
int main(int argc, char *argv[]) {
	int fd, led_num, led_c;
	char *leds = "/dev/leds";	//led设备文件

	led_num = LED_NUM;
	led_c = LED_C;

	printf("argv1 is cmd;argv2 is io\n");
	if(atoi(argv[1])>=led_c) {
		printf("argv[1] is 0 or 1\n");
	}else if(atoi(argv[2])>=led_num) {
		printf("argv[2] is 0 or 1\n");
	}
	
	if((fd = open(leds, O_RDWR|O_NOCTTY|O_NDELAY)) < 0) {
		printf("open %s failed\n", leds);
	}else {
		ioctl(fd, atoi(argv[1]), atoi(argv[2]));
		printf("ioctl %s success\n", leds);
	}

	close(fd);
	return 0;
}
