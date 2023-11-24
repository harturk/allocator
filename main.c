#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "mymemory.h"
#include "list.c"
#include "mymemory.c"

int main() {
    int size = 200;
    mymemory_t *pool = mymemory_init(size);
    allocation_t *block = mymemory_alloc(pool, 2 * sizeof(int));
    allocation_t *block2 = mymemory_alloc(pool, 2 * sizeof(int));
    allocation_t *block3 = mymemory_alloc(pool, 2 * sizeof(char));

    printf("------------------- Informacoes sobre a memoria -------------------\n");
    mymemory_display(pool);
    printf("\n");
    mymemory_stats(pool);
    free_block_display();
    printf("\n");
    printf("Apos limpeza\n");
    mymemory_free(pool, block2->start + 20);
    mymemory_display(pool);
    free_block_display();
    printf("\n");
    mymemory_stats(pool);
    printf("\n");
    printf("Limpando a memoria\n");
    mymemory_cleanup(pool);
    printf("Apos limpeza\n");
    mymemory_display(pool);

    return 0;
}