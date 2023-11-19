#include <stdio.h>
#include "mymemory.h"
#include "mymemory.c"

int main() {
    mymemory_t* memory = mymemory_init(1000);
    if (memory == NULL) {
        printf("Falha ao inicializar o gerenciador de memória.\n");
        return 1;
    }

    void* alloc1 = mymemory_alloc(memory, 1000);
    void* alloc2 = mymemory_alloc(memory, 400);
    void* alloc3 = mymemory_alloc(memory, 100);
    mymemory_display(memory);


    mymemory_free(memory, alloc2);

    printf("\nEstatísticas de memória:\n");
    mymemory_stats(memory);

    mymemory_cleanup(memory);

    return 0;
}