#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// #include <sys/mman.h>
#include <string.h>
#include "mymemory.h"

typedef struct {
    void *start;
    void *end;
    void size;
} occupied_space

static mymemory_t *p;

mymemory_t *getMymemory_t()
{
    return p;
}


allocation_t *allocate_block(mymemory_t *pool, size_t size)
{
    if (size > pool->total_size) {
        printf("Tamanho do bloco maior que o tamanho total do pool\n");
        return NULL;
    }
    allocation_t *block = malloc(sizeof(allocation_t));
    if (block == NULL) {
        printf("Erro ao alocar bloco\n");
        return NULL;
    }
    // block = (allocation_t *)&pool[size + sizeof(mymemory_t)];
    // block->start = &pool[size + sizeof(mymemory_t)];
    block->size = size;
    block->next = NULL;
    // Insere no head caso ainda não tenha sido alocado algum bloco
    if (pool->head == NULL) {
        pool->head = block;
    }
    printf("Block Criado no endereco %p\n", block);
    return block;
}

mymemory_t *mymemory_init(size_t size)
{
    // Inicializa p, caso ainda nao tenha sido inicializado.
    // A ideia é que este método seja rodado apenas um vez, para criar um pool único de memória.
    if (p == NULL)
    {
        p = malloc(sizeof(mymemory_t));
        p->pool = malloc(size);
        p->total_size = size;
        p->head = NULL;
        printf("Pool Criado no endereco %p --- Tamanho %d\n", p->pool, sizeof(p->pool));
        return p;
    }

    return p;
}

void* mymemory_alloc(mymemory_t *pool, size_t size)
{
    // Inicializa, caso não tenha sido inicializado ainda.
    if (pool == NULL) {
        printf("pool == NULL\n");
        pool = mymemory_init(size);
    }

    // FIRST FIT
    return allocate_block(pool, size);
    return block->start;
}