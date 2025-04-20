#include "core_malloc.h"

size heap_index = 0;



void *core_malloc(size size)
{
    if (heap_index + size > heap_size)
    {
         return NULL; // Out of memory
    }

    void *ptr = &heap[heap_index];
    heap_index += size;
    return ptr;
}

void core_free(void *ptr)
{
    if (ptr >= (void *)&heap[0] && ptr < (void *)&heap[heap_size])
    {
        heap_index = (char *)ptr - (char *)&heap[0];
    }
}