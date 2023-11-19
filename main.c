#include <stdio.h>
#include "mymemory.h"
#include "mymemory.c"

int main() {
    // Como o pool de memória é estático, foi criado um método auxiliar para buscar
    // o ponteiro para o pool de memória.
    int size = 200;
    mymemory_t *static_pool = mymemory_init(200);
    allocation_t *block = mymemory_alloc(static_pool, 2 * sizeof(int));

    printf("inicio do pool: %p\n", static_pool->pool);
    printf("fim do pool: %p\n", size + static_pool->pool);

    printf("inicio do pool: %p\n", block);
    printf("fim do pool: %p\n", 2 * sizeof(int) + block);

    return 0;
}