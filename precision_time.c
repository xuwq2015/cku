#include <stdio.h>
#include <sys/time.h>

void function() {
	unsigned int i, j;
	double y;
	
	for(i = 0; i < 1000; i++) {
		for(j = 0; j < 1000; j++) {
			y = i / (j + 1);
		}
	}
}

int main() {
	struct timeval tpatart, tpend;
	float timeuse;

	gettimeofday(&tpatart, NULL);	//获取开始时间

	function();

	gettimeofday(&tpend, NULL);	//获取结束时间

	//计算所用时间
	timeuse = 1000000 * (tpend.tv_sec - tpatart.tv_sec) + tpend.tv_usec - tpatart.tv_usec;

	timeuse /= 1000000;	//将时间转换为妙

	printf("所用时间:%f秒\n", timeuse);
	return 0;
}
