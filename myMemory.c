#include <stdlib.h>
#include <stdio.h>
#include "mymemory.h"

static mymemory_t* p;

allocation_t* allocate_block(size_t size) {
    allocation_t *block = (allocation_t *)&p[size + sizeof(allocation_t)];
    block->size = sizeof(block);
    block->start = &p[size + sizeof(allocation_t)];
    block->next = NULL;
    return block;
}

mymemory_t* mymemory_init(size_t size) {
    if (p == NULL) {
        p= malloc(sizeof(mymemory_t));
        p->pool = malloc(8);
        p->total_size = 8;
        allocation_t block = allocate_block(size);
        p->head = block;
        printf("Pool Criado\n");
        return p;
    }

    allocation_t* lastBlock = p->head;
    while(p->head->next != NULL) {
        lastBlock = p->head->next;
    }
    struct allocation block = allocate_block(size);
    lastBlock->next = block;

    return p;
}

