#include "log.h"
#include <time.h>

const char *getTimeFormat(const char *fmt) {
	static char buf[128];
	time_t seconds = time(NULL);
	struct tm *local = localtime(&seconds);
	sprintf(buf, "%4d-%02d-%02d %02d:%02d:%02d",
			local->tm_year+1900, local->tm_mon+1, local->tm_mday,
			local->tm_hour, local->tm_min, local->tm_sec);
	return buf;
}
