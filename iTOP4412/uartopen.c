/* 串口操作 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <error.h>

int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop) {	//串口初始化函数
	/*
		fd:串口文件描述符
		nSpeed:波特率
		nBits:比特大小
		nEvent:奇偶校验
		nStop:停止位
	*/
	
	struct termios newtio, oldtio;
	
	/* 读取串口原有参数 */
	if(tcgetattr(fd, &oldtio) != 0) {
		perror("SetupSerial 1");
		return -1;
	}
	bzero(&newtio, sizeof(newtio));
	
	/* 设置控制模式 */
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;
	
	/* 设置数据比特位长度，一个字节7/8个比特位 */
	switch(nBits) {
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}
	
	/* 奇偶校验 */
	switch(nEvent) {
		case 'O':	//奇校验
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case 'E':	//偶校验
			newtio.c_iflag |= (INPCK | ISTRIP);
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			break;
		case 'N':	//不做校验
			newtio.c_cflag &= ~PARENB;
			break;
	}
	
	/* 波特率 */
	switch(nSpeed) {
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	
	/* 停止位 */
	if(nStop == 1) {
		newtio.c_cflag &= ~CSTOPB;
	}else if(nStop == 2) {
		newtio.c_cflag |= CSTOPB;
		newtio.c_cc[VTIME] = 0;
		newtio.c_cc[VMIN] = 0;
		
		//清空串口缓冲区数据
		tcflush(fd, TCIFLUSH);
		
		//设置串口参数
		if((tcsetattr(fd, TCSANOW, &newtio)) != 0) {
			perror("com set crror");
			return -1;
		}
	}
	
	retrun 0;
}

int main(int argc, int *argv[]) {
	int fd;
	char *uart3 = "/dev/ttySAC3";
	
	/* 打开串口文件 */
	if((fd = open(uart3, O_RDWR|O_CREAT, 0777)) < 0) {
		perror("open");
		exit(1);
	}else {
		printf("open %s is success!\n", uart3);
	}
	
	/* 初始化串口 */
	if((set_opt(fd, 115200, 8, 'N', 1)) < 0) {
		printf("ttr init error\n");
		exit(1);
	}
	
	close(fd);
	retrun 0;
}