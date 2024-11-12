#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "vmlib.h"
#include "vm.h"

int main()
{
    vminit(1024);

    void *ptr = vmalloc(16);
    struct block_header *hdr = (struct block_header *)
                               ((char *)ptr - sizeof(struct block_header));
    assert(ptr != NULL);
    assert((uint64_t)ptr % 16 == 0);
    assert((char *)ptr - (char *)heapstart == sizeof(struct block_header));
    assert(hdr->size_status == 35);

    void *ptr2 = vmalloc(4);
    hdr = (struct block_header *)((char *)ptr2 - sizeof(struct block_header));

    assert(ptr2 != NULL);
    assert((uint64_t)ptr2 % 16 == 0);
    assert((char *)ptr2 - (char *)ptr == 32);
    assert(hdr->size_status == 19);

    vmdestroy();
    return 0;
}
