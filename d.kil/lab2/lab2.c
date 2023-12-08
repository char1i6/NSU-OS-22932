#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	
	putenv("TZ=America/Los_Angeles");
	time_t tm = time(0);
	char california[40] = {};
	ctime_r(&tm, california, 40);
	printf("%s", california);
	exit(0);
}
