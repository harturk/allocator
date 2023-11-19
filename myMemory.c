#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h";
#include "list.h";

mymemory_init* mymemory_init(size_t size) {
    mymemory_t *memory = malloc(sizeof(mymemory_t));
    memory->pool = malloc(size);
    memory->total_size = size;
    memory->head = NULL;
    return memory;
}