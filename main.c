#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "mymemory.h"
// #include "list.c"
// #include "mymemory.c"

int main()
{
	int size = 200;
	mymemory_t *pool = mymemory_init(size);
	// allocation_t *block = mymemory_alloc(pool, 2 * sizeof(int));
	// allocation_t *block2 = mymemory_alloc(pool, 2 * sizeof(int));
	allocation_t *block3 = mymemory_alloc(pool, 4 * sizeof(char));
	allocation_t *block4 = mymemory_alloc(pool, 8 * sizeof(char));
	allocation_t *block5 = mymemory_alloc(pool, 12 * sizeof(char));

	char *c = block3->start;
	for (int i = 0; i < block3->size; i++)
	{
		c[i] = 'a';
	}
	c[block3->size] = '\0';

	char *d = block4->start;
	for (int i = 0; i < block4->size; i++)
	{
		d[i] = 'b';
	}
	d[block4->size] = '\0';

	char *e = block5->start;
	for (int i = 0; i < block5->size; i++)
	{
		e[i] = 'c';
	}
	e[block5->size] = '\0';

	mymemory_free(pool, block4->start);
	block4 = mymemory_alloc(pool, 8 * sizeof(char));
	for (int i = 0; i < block4->size; i++)
	{
		printf("%c", d[i]);
	}

	for (int i = 0; i < block5->size; i++)
	{
		printf("%c", e[i]);
	}

	printf("\n");
	printf("------------------- Memoria -------------------\n");
	mymemory_display(pool);
	mymemory_stats(pool);
	free_block_display();
	mymemory_free(pool, block3->start);
	printf("\n");

	// LIMPEZA
	mymemory_cleanup(pool);
	printf("------------------- Memoria -------------------\n");
	mymemory_display(pool);
	mymemory_stats(pool);
	free_block_display();

	// printf("\n");
	// printf("Apos limpeza\n");
	// mymemory_free(pool, block2->start);
	// mymemory_display(pool);
	// free_block_display();
	// printf("\n");
	// mymemory_stats(pool);
	// printf("\n");
	// printf("BEEEEEEEEEEEEEEEEEEEEEEEEEEEST FIT\n");
	// allocation_t *block4 = mymemory_alloc(pool, 2 * sizeof(char));
	// free_block_display();
	// printf("Limpando a memoria\n");
	// mymemory_cleanup(pool);
	// printf("Apos limpeza\n");
	// mymemory_display(pool);

	return 0;
}