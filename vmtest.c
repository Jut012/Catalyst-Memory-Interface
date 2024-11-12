#include <stdio.h>

#include "vmlib.h"

int main()
{
    vminit(2000); 


    void *ptr = vmalloc(16);

    vminfo(); 
            

    vmdestroy(); 
    return 0;
}
