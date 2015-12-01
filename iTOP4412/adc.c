#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <error.h>

#define BUFFER_LEN 512

int main(int argc, int *argv[]) {
	int fd;
	char *adc = "/dev/adc";
	char buffer[BUFFER_LEN];
	int len = 0, r = 0;
	
	memset(buffer, 0, sizeof(buffer));
	printf("adc ready\n");
	
	if((fd = open(adc, O_RDWR|O_NOCTTY|O_NDELAY)) < 0) {
		perror("open");
		exit(1);
	}else {
		printf("open adc success\n");
		
		len = read(fd, buffer, BUFFER_LEN);
		
		if(len = 0)
			printf("return null\n");
		else {
			r = atoi(buffer);
			r = (int)(r * 10000 / 4095);
			printf("res value is %d\n", r);
		}
	}
	return 0;
}
