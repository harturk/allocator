#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "mymemory.h"
#include "list.c"
#include "mymemory.c"

int main() {
    // Como o pool de memória é estático, foi criado um método auxiliar para buscar
    // o ponteiro para o pool de memória.
    int size = 200;
    mymemory_t *static_pool = mymemory_init(size);
    allocation_t *block = mymemory_alloc(static_pool, 2 * sizeof(int));
    
    // struct list_s *lst;
	// struct node_s *node;

    // free_block *a1 = malloc(sizeof(free_block));
    // free_block *a2 = malloc(sizeof(free_block));
    // a1->start = static_pool->pool;
    // a1->size = 200;
    // a1->end = static_pool->pool + 200;
	
	// lst = list_create();
    // node = list_push(lst, (void*)a1);

    // printf("inicio do pool: %p\n", static_pool->pool);
    // printf("fim do pool: %p\n", size + static_pool->pool);
    // a2 = (void*)node->data;

    // printf("teste: %p\n", a2->start);
    // printf("teste: %d\n", a2->size);

    printf("------------------- Informacoes sobre a memoria -------------------\n");
    mymemory_display(static_pool);
    printf("\n");
    mymemory_stats(static_pool);
    printf("\n");
    mymemory_display(static_pool);
    printf("\n");
    mymemory_stats(static_pool);

    return 0;
}