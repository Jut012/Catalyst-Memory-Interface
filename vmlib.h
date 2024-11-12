
#ifndef VMLIB_H
#define VMLIB_H

#include <stddef.h>

int vminit(size_t sz);
void vmdestroy();

void *vmalloc(size_t size);
void vmfree(void *ptr);

void vminfo();
void vmdump(const char *filename);
int vmload(const char *filename);

#endif 
