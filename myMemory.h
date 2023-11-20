#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include "list.h"

// Estrutura de alocação, onde indica o ínicio do ponteiro da estrutura alocada, tamanho de sua alocação
// e um ponteiro para a próxima estrutura alocada. REPRESENTAÇÃO DO BLOCO DE MEMÓRIA
typedef struct allocation {
    void* start;
    size_t size;
    struct allocation* next;
} allocation_t;


// Essa estrutura está referenciando referências para o armazenamento total. REPRESENTAÇÃO DA POOL DE MEMÓRIA
typedef struct {
    void* pool;
    size_t total_size;
    allocation_t* head;
} mymemory_t;

typedef struct {
    void* start;
    void* end;
    size_t size;
} free_block;

// Atualiza lista de blocos livres
void update_list(struct node_s *node_block, size_t size);

// Aloca o bloco de memória total e retorna um ponteiro para ele
mymemory_t* mymemory_init(size_t size);

// Procura pelo bloco livre mais próximo do tamanho especificado
struct node_s *find_next_free_block(size_t size);

// Tenta alocar um bloco de memória de tamanho especificado. Se a alocação for bem-sucedida, 
// retorna um ponteiro para o início do bloco. Caso contrário, retorna NULL.
void* mymemory_alloc(mymemory_t *memory, size_t size);

// // Libera a alocação apontada por ptr. Se ptr não for uma alocação válida, a função
// // não deve fazer nada.
// void mymemory free(mymemory t *memory, void *ptr);

// // Exibe todas as alocações atuais, incluindo o início e o tamanho de cada alocação
// void mymemory display(mymemory t *memory);

// // Exibe estatísticas gerais sobre a memória, incluindo:
// //      – Número total de alocações
// //      – Memória total alocada (em bytes)
// //      – Memória total livre (em bytes)
// //      – O maior bloco contíguo de memória livre
// //      – Número de fragmentos de memória livre (ou seja, blocos de memória entre alocações)
// void mymemory stats(mymemory t *memory);

// // Libera todos os recursos (incluindo todas as alocações e o bloco de memória total)
// void mymemory cleanup(mymemory t *memory);

#endif