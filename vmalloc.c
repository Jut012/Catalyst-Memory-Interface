#include "vm.h"
#include "vmlib.h"

void *vmalloc(size_t size)
{
    if (size == 0) {
	    return NULL;
    }

    size_t required_size =
        ROUND_UP(size + sizeof(struct block_header), BLKALIGN);

    struct block_header *current = heapstart;
    struct block_header *best_fit = NULL;
    size_t best_fit_size = SIZE_MAX;

    while (current->size_status != VM_ENDMARK) {
        size_t current_size = BLKSZ(current);

        if (!(current->size_status & VM_BUSY) &&
            current_size >= required_size) {
            if (current_size < best_fit_size) {
                best_fit = current;
                best_fit_size = current_size;
            }
        }

        current = (struct block_header *)((char *)current + current_size);
    }

    if (best_fit == NULL) {
	    return NULL;
    }

    if (best_fit_size >=
        required_size + sizeof(struct block_header) + BLKALIGN) {
        size_t remaining_size = best_fit_size - required_size;

        struct block_header *new_free_block =
            (struct block_header *)((char *)best_fit + required_size);
        new_free_block->size_status =
            remaining_size | (best_fit->size_status & VM_PREVBUSY);

        struct block_footer *footer =
            (struct block_footer *)((char *)new_free_block + remaining_size -
                                    sizeof(struct block_footer));
        footer->size = remaining_size;

        best_fit->size_status =
            required_size | VM_BUSY | (best_fit->size_status & VM_PREVBUSY);

        struct block_header *next_block =
            (struct block_header *)((char *)new_free_block + remaining_size);
        if (next_block->size_status != VM_ENDMARK) {
            next_block->size_status &= ~VM_PREVBUSY;
        }
    } else {
        best_fit->size_status |= VM_BUSY;
    }
    return (void *)((char *)best_fit + sizeof(struct block_header));
}
