#ifndef VM_H
#define VM_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define malloc(x) NULL
#define calloc(x) NULL
#define realloc(x) NULL
#define reallocarray(x) NULL

#define VM_ENDMARK 0x1

#define VM_BLKSZMASK 0xFFFFFFFFFFFFFFFC
#define VM_BUSY 0x1
#define VM_PREVBUSY 0x2

#define BLKSZ(b) ((b)->size_status & VM_BLKSZMASK)
#define ROUND_UP(N, S) ((((N) + (S)-1) / (S)) * (S))
#define BLKALIGN 16

struct block_header {
    size_t size_status;
};

struct block_footer {
    size_t size;
};

extern struct block_header *heapstart;

#endif 