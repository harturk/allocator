#include <stdlib.h>
#include <stdio.h>
#include "mymemory.h"

mymemory_t* mymemory_init(size_t size) {
    mymemory_t* memory = malloc(sizeof(mymemory_t));
    memory->pool = malloc(size);
    memory->total_size = size;
    memory->head = NULL;
    return memory;
}

void* mymemory_alloc(mymemory_t* memory, size_t size) {
    if(memory-> total_size <size){
        printf("Erro: Memoria insuficiente");
        return NULL;
    }
    allocation_t* allocation = malloc(sizeof(allocation_t));
    allocation->size = size;
    allocation->next = memory->head;
    memory->head = allocation;
    return allocation->start = malloc(size);
}

void mymemory_free(mymemory_t* memory, void* ptr) {
    allocation_t* allocation = memory->head;
    allocation_t* prev = NULL;
    while (allocation != NULL) {
        if (allocation->start == ptr) {
            free(ptr);
            if (prev == NULL) {
                memory->head = allocation->next;
            } else {
                prev->next = allocation->next;
            }
            free(allocation);
            return;
        }
        prev = allocation;
        allocation = allocation->next;
    }
}

void mymemory_display(mymemory_t* memory) {
    printf("Memoria: %p\n", memory->pool);
    printf("Tamanho total: %zu\n", memory->total_size);
    printf("Alocacoes:\n");
    allocation_t* allocation = memory->head;
    while (allocation != NULL) {
        printf("- %p (%zu bytes)\n", allocation->start, allocation->size);
        allocation = allocation->next;
    }
}

void mymemory_stats(mymemory_t* memory) {
    size_t allocated = 0;
    allocation_t* allocation = memory->head;
    while (allocation != NULL) {
        allocated += allocation->size;
        allocation = allocation->next;
    }
    printf("Memoria: %p\n", memory->pool);
    printf("Tamanho total: %zu\n", memory->total_size);
    printf("Alocacoes: %zu bytes\n", allocated);
    printf("Espaço livre: %zu bytes\n", memory->total_size - allocated);
}

void mymemory_cleanup(mymemory_t* memory) {
    allocation_t* allocation = memory->head;
    while (allocation != NULL) {
        allocation_t* next = allocation->next;
        free(allocation->start);
        free(allocation);
        allocation = next;
    }
    free(memory->pool);
    free(memory);
}