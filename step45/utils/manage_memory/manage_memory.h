#include <stdlib.h>

#ifndef _MANAGE_MEMORY_H_
#define _MANAGE_MAMORY_H_

typedef struct mem_t {
    void *ptr;
    size_t size;
    const char *file;
    unsigned int line;
} MEM_T;

#define MEM_INFO_SIZE 100000

int mem_info_num;
MEM_T mem_info[MEM_INFO_SIZE];
void leak_detect_init();
void* leak_detect_malloc(size_t size, const char *file, unsigned int line);
void leak_detect_free(void *ptr);
void leak_detect_all_free();
void leak_detect_check();

#define mymalloc(size) leak_detect_malloc(size, __FILE__, __LINE__)

#endif // _MANAGE_MEMORY_H_