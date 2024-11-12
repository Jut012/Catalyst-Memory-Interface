#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "vmlib.h"
#include "vm.h"

int main()
{
    vminit(4096);

    void *ptr1 = vmalloc(64);
    void *ptr2 = vmalloc(64);
    vmalloc(64);

    vmfree(ptr2);

    vmfree(ptr1);

    void *ptr4 = vmalloc(144);
    assert(ptr1 == ptr4);

    vmdestroy();
    return 0;
}