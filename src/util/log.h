#ifndef XUI_util_log_h
#define XUI_util_log_h

#include <stdio.h>

const char *getTimeFormat(const char *fmt);


#define CSI_BLACK	"\x1B[1;30m"
#define CSI_RED		"\x1B[1;31m"
#define CSI_GREEN	"\x1B[1;32m"
#define CSI_YELLOW	"\x1B[1;33m"
#define CSI_BLUE	"\x1B[1;34m"
#define CSI_PURPLE	"\x1B[1;35m"
#define CSI_CYAN	"\x1B[1;36m"
#define CSI_WHITE	"\x1B[1;37m"
#define CSI_END		"\x1B[0m"

#define CSIM_LOG	"\x1B[1;32m"
#define CSIM_DEBUG	"\x1B[1;36m"
#define CSIM_WARNING	"\x1B[1;7;33;37m"
#define CSIM_ERROR	"\x1B[1;7;31;47m"
#define CSIM_FILE	"\x1B[1;4;32m"
#define CSIM_FUNC	"\x1B[1;3;37m"

#define Log(msg, args...) do { \
	printf(CSIM_LOG "%s L: " CSI_END, getTimeFormat(NULL)); \
	printf(msg, ##args); \
	printf("\n"); \
} while (0)

#define Assert(condition, msg, args...) do { \
	if (!(condition)) { \
		fprintf(stderr, CSIM_ERROR "Assert Fail:" CSI_END); \
		fprintf(stderr, " "); \
		fprintf(stderr, msg, ##args); \
		fprintf(stderr, "\n"); \
		exit(1); \
	} \
} while (0)

#define Cannot(condition) Assert(!(condition), #condition)

#define Debug(msg, args...) do { \
	printf(CSIM_DEBUG "Debug:" CSI_END); \
	printf(" "); \
	printf(msg, ##args); \
	printf("\n"); \
} while (0)

#define DebugPrint(msg, args...) do { \
	printf(CSIM_FILE __FILE__ ":%d" CSI_END " in " CSIM_FUNC "%s" CSI_END ": ", __LINE__, __FUNCTION__ ); \
	printf(msg, ##args); \
	printf("\n"); \
} while (0)

#define Error(msg, args...) do { \
	printf(CSIM_FILE __FILE__ ":%d" CSI_END " in " CSIM_FUNC "%s" CSI_END ": ", __LINE__, __FUNCTION__ ); \
	printf(CSIM_ERROR "Error:" CSI_END); \
	printf(" "); \
	printf(msg, ##args); \
	printf("\n"); \
} while (0)

#define NotImplemented() DebugPrint("Not Implemented")

#endif
