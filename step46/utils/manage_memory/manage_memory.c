#include "manage_memory.h"
#include <stdio.h>

int mem_info_num = 0;

void leak_detect_init() {
  for (int i = 0; i < MEM_INFO_SIZE; i++){
    mem_info[i].ptr = NULL;
    mem_info[i].size = 0;
    mem_info[i].file = NULL;
    mem_info[i].line = 0;
  }
}

void* leak_detect_malloc(size_t size, const char *file, unsigned int line) {
  void *ptr = NULL;

  ptr = malloc(size);
  if (ptr == NULL)
    return NULL; 
  for (int i = 0; i < MEM_INFO_SIZE; i++) {
    if(mem_info[i].ptr == NULL){
      mem_info[i].ptr = ptr;
      mem_info[i].size = size;
      mem_info[i].file = file;
      mem_info[i].line = line;
      mem_info_num++;
      break;
    }
  }

  return ptr;
}

void leak_detect_free(void *ptr) {
  for (int i = 0; i < MEM_INFO_SIZE; i++) {
    if (mem_info[i].ptr == ptr) {
      mem_info[i].ptr = NULL;
      mem_info[i].size = 0;
      mem_info[i].file = NULL;
      mem_info[i].line = 0;
      mem_info_num--;
      break;
    }
  }
  free(ptr);
}

void leak_detect_all_free() {
  for (int i = 0; i < MEM_INFO_SIZE; i++) {
    if (mem_info[i].ptr != NULL) {
      free(mem_info[i].ptr);
      mem_info[i].ptr = NULL;
      mem_info[i].size = 0;
      mem_info[i].file = NULL;
      mem_info[i].line = 0;
      mem_info_num--;
      if (mem_info_num == 0)
        break;
    }
  }
}

void leak_detect_check() {
  if (mem_info_num == 0) {
    printf("No memory leak.\n");
    return;
  } else {
    printf("Memory leak detected.\n");
    for (int i = 0; i < MEM_INFO_SIZE; i++) {
      if (mem_info[i].ptr != NULL){
        printf(" adr:%p\n", mem_info[i].ptr);
        printf(" size:%u\n", (unsigned int)mem_info[i].size);
        printf(" place:%s:%u\n", mem_info[i].file, mem_info[i].line);
        printf("\n");
      }
    }
  }
}