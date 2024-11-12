#include "vm.h"
#include "vmlib.h"

void vmfree(void *ptr)
{
    if (ptr == NULL) return;

    struct block_header *header = (struct block_header *)((char *)ptr - sizeof(struct block_header));

    if (!(header->size_status & VM_BUSY)) return;

    header->size_status &= ~VM_BUSY;

    struct block_header *next_header = (struct block_header *)((char *)header + BLKSZ(header));
    if (!(next_header->size_status & VM_BUSY)) {
	    header->size_status += BLKSZ(next_header);
    }

    if (!(header->size_status & VM_PREVBUSY)) {
	    struct block_footer *prev_footer = (struct block_footer *)((char *)header - sizeof(struct block_footer));
	    struct block_header *prev_header = (struct block_header *)((char *)header - prev_footer->size);
	    prev_header->size_status += BLKSZ(header);
	    header = prev_header;
    }

    struct block_footer *footer = (struct block_footer *)((char *)header + BLKSZ(header) - sizeof(struct block_footer));
    footer->size = BLKSZ(header);

    next_header = (struct block_header *)((char *)header + BLKSZ(header));
    if (next_header->size_status != VM_ENDMARK) {
	    next_header->size_status &= ~VM_PREVBUSY;
	}
}
