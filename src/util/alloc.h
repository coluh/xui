#ifndef XUI_UTIL_ALLOC_H
#define XUI_UTIL_ALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static inline void *callo(unsigned long nmemb, unsigned long size) {
	void *p = calloc(nmemb, size);
	if (p == NULL) {
		perror("Out of memory");
		exit(1);
	}
	return p;
}

static inline void *reallo(void *ptr, unsigned long size) {
	void *p = realloc(ptr, size);
	if (p == NULL) {
		perror("Out of memory");
		exit(1);
	}
	return p;
}

#endif
