#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "vmlib.h"
#include "vm.h"

int main()
{
    vmload("img/no_free.img");
    
    void *ptr = (char *)heapstart + 1288;
    vmfree(ptr);

    ptr = vmalloc(64);
    assert(ptr != NULL);

    vmdestroy();
    return 0;
}