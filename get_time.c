/* 获取系统时间 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	time_t t;
	char *ctime_time;
	struct tm *gm_time;
	
	t =  time(NULL);	//获取机器格式时间

	ctime_time = ctime(&t);	//时间格式转换
	printf("ctime:%s\n", ctime_time);

	gm_time = gmtime(&t);	//将机器时间转换为tm结构体格式
	printf("gmtime:%d %d %d %d %d %d %d %d %d\n", gm_time->tm_sec, gm_time->tm_min, gm_time->tm_hour, gm_time->tm_mday, gm_time->tm_mon, gm_time->tm_year, gm_time->tm_wday, gm_time->tm_yday, gm_time->tm_isdst);

	printf("asctime:%s\n", asctime(gm_time));

	printf("localtime_asctime:%s\n", asctime(localtime(&t)));
	return 0;
}
