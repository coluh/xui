#ifndef XUI_util_alloc_h
#define XUI_util_alloc_h

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
