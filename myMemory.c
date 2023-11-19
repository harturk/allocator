#include <stdio.h>
#include <stdlib.h>
#include "myMemory.h";
#include "list.h";

myMemory_t* myMemory_init(size_t size) {
    myMemory_t *memory = malloc(sizeof(myMemory_t));
    memory->pool = malloc(size);
    memory->total_size = size;
    memory->head = NULL;
    return memory;
}