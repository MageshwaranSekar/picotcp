/*********************************************************************
PicoTCP. Copyright (c) 2012-2015 Altran Intelligent Systems. Some rights reserved.
See LICENSE and COPYING for usage.
*********************************************************************/

#ifndef PICO_PIP
#define PICO_PIP
#include <stddef.h>
#include <stdint.h>

extern void *myMalloc(uint32_t size);
extern void myFree(void *ptr);

extern int printf(const char *format, ...);
extern void malloc_init();
extern int memcmp(const void *s1, const void *s2, size_t n);
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset( void * ptr, int value, size_t num );
extern char *strcat(char* dest, const char* source);
extern size_t strlen(const char* str);
extern void *strcpy(char* dest, const char* src);
extern char *strncpy(char *dest, const char *src, size_t count);
extern int strcmp(const char *cs, const char *ct);
extern int strcasecmp(const char *cs, const char *ct);
extern int strncmp(const char *s1, const char *s2, size_t n);
extern char *strstr(const char *str, const char *pattern);
extern void *memmove(void *str1, const void *str2, size_t n);
extern char *strnstr(const char *str, const char *pattern, size_t len);
extern char *strncpy(char *dest, const char *src, size_t n);
extern int tolower(int ch);
extern int isalpha(int ch);
extern int toupper(int ch);

#define pico_zalloc(x) myMalloc(x)
#define pico_free(x) myFree(x)

#ifndef PIPDBG
#define PIPDBG
//#define dbg(a,...) printf("[TRACE] " a "\r\n", ##__VA_ARGS__);
#define dbg(...)
#endif




#ifndef NULL
#define NULL ((void *)0)
#endif
extern uint32_t pip_time(void);


static inline unsigned long PICO_TIME(void){
	unsigned long tick=pip_time();
	return tick / 1000;
}

static inline unsigned long PICO_TIME_MS(void){
	unsigned long tick=pip_time();
	return tick;
}

static inline void PICO_IDLE(void){
	unsigned long tick_now = pip_time();
	while(tick_now == pip_time());
	//while(pip_time() < tick_now+10);
}

#endif  /* PICO_PIP */
