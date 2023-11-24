#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"
#include "list.h"

static struct list_s *lst;

void update_list(struct node_s *node_block, size_t size)
{
    free_block *block = (void *)node_block->data;
    block->size = block->size - size;
    block->start = block->start + size + 1;
}

struct node_s *find_next_free_block(size_t size)
{
    // Percorre a lista de blocos livres
    if (lst == NULL || lst->head == NULL)
    {
        // printf("Lista de blocos livres vazia\n");
        return NULL;
    }
    // printf("Procurando bloco livre\n");
    size_t current_size;
    size_t closest_size;
    free_block *closest_block;
    struct node_s *current_node;
    struct node_s *closest_node;

    // printf("Alocando blocos auxiliares\n");
    current_node = list_index(lst, 0);
    free_block *current_block = (void *)current_node->data;
    current_size = current_block->size;
    if (current_size > size)
    {
        closest_node = current_node;
        closest_block = current_block;
        closest_size = current_size;
    }
    // printf("Testando tamanhos iniciais\n");

    // Procura pelo bloco livre mais próximo do tamanho especificado
    while (current_node->next != NULL)
    {
        // Pega o bloco de tamanho mais próximo
        current_block = (void *)current_node->data;
        current_size = current_block->size;
        // Best-Fit
        // Se o tamanho atual for menor que o tamanho mais próximo (iterado anteriormente) e
        // e maior que o tamanho desejado, atualiza o bloco mais próximo
        if (size < current_size && current_size < closest_size)
        {
            closest_block = current_block;
            closest_size = current_size;
        }
        current_node = current_node->next;
    }
    if (closest_block == NULL)
    {
        // printf("Nenhum bloco adequado foi encontrado\n");
        return NULL;
    }
    printf("Bloco mais proximo encontrado no endereço %p ---- Tamanho %zu\n", closest_block, closest_block->size);
    return closest_node;
}

void *mymemory_alloc(mymemory_t *memory, size_t size)
{
    if (size > memory->total_size)
    {
        printf("Tamanho do bloco maior que o tamanho total do pool\n");
        return NULL;
    }
    allocation_t *allocation_block = malloc(sizeof(allocation_t));
    if (allocation_block == NULL)
    {
        printf("Erro ao alocar bloco\n");
        return NULL;
    }

    printf("Validacoes de tamanho\n");

    // Informações sobre o próximo bloco livre na memória
    struct node_s *next_node = find_next_free_block(size);
    if (next_node == NULL)
    {
        return NULL;
    }
    free_block *next_block = (void *)next_node->data;

    printf("Criados blocos auxiliares\n");

    allocation_block->start = next_block->start;
    allocation_block->size = size;
    allocation_block->next = NULL;
    update_list(next_node, size);
    // Insere no head caso ainda não tenha sido alocado algum bloco
    if (memory->head == NULL)
    {
        memory->head = allocation_block;
    }
    else
    {
        // Aloca o bloco no final da pool
        allocation_t *current_block = memory->head;
        while (current_block->next != NULL)
        {
            current_block = current_block->next;
        }
        current_block->next = allocation_block;
    }
    printf("Block Criado no endereco %p\n", allocation_block);
    return allocation_block;
}

mymemory_t *mymemory_init(size_t size)
{
    mymemory_t *p;
    p = malloc(sizeof(mymemory_t));
    p->pool = malloc(size);
    p->total_size = size;
    p->head = NULL;
    printf("Pool Criado no endereco %p --- Tamanho %zu\n", p->pool, sizeof(size));
    free_block *current_block = malloc(sizeof(free_block));
    current_block->start = p->pool;
    current_block->size = size;

    lst = list_create();
    list_push(lst, (void *)current_block);
    printf("Lista criada\n");
    return p;
}

void mymemory_free(mymemory_t *memory, void *ptr)
{
    // Libera a alocação apontada por ptr. Se ptr não for uma alocação válida, a função
    // não deve fazer nada.
    allocation_t *current_block = memory->head;
    allocation_t *previous_block = NULL;
    while (current_block != NULL)
    {
        // Será limpado o bloco que contém o ponteiro dentro do seu intervalo de memória
        if (ptr >= current_block->start && ptr <= current_block->start + current_block->size )
        {
            // Se for o primeiro bloco, atualiza o head
            if (previous_block == NULL)
            {
                memory->head = current_block->next;
            }
            else
            {
                previous_block->next = current_block->next;
            }
            // Insere o bloco na lista de blocos livres
            free_block *new_block = malloc(sizeof(free_block));
            new_block->start = current_block->start;
            new_block->size = current_block->size;
            list_push(lst, (void *)new_block);
            // Libera o bloco
            free(current_block);
            return;
        }
        previous_block = current_block;
        current_block = current_block->next;
    }
    printf("Nenhuma alocacao encontrada\n");
}

void mymemory_cleanup(mymemory_t *memory)
{
    // Libera todos os recursos (incluindo todas as alocações e o bloco de memória total)
    allocation_t *current_block = memory->head;
    allocation_t *next_block = NULL;
    while (current_block != NULL)
    {
        next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }

    // Fiquei na dúvida sobre a necessidade de atribuir NULL após executar o free
    // porem, após testes, o programa devolvia outros enderecos de memória
    // quando nao havia a atribuição de NULL
    free(memory->pool);
    memory->pool = NULL;
    memory->head = NULL;
    free(memory);
    memory = NULL;

    // Libera todos os blocos de memoria livre
    struct node_s *current_node = list_index(lst, 0);
    free_block *current_free_block = (void *)current_node->data;
    while (current_node->next != NULL)
    {
        current_free_block = (void *)current_node->data;
        free(current_free_block);
        current_node = current_node->next;
        free(current_node->prev);
        current_node->prev = NULL;
        printf("Bloco livre liberado\n");
    }
    free(lst);
    lst = NULL;

}

void mymemory_display(mymemory_t *memory)
{
    if (memory->head == NULL)
    {
        printf("Nenhum bloco alocado\n");
        return;
    }
    // Exibe todas as alocações atuais, incluindo o início e o tamanho de cada alocação
    allocation_t *current_block = memory->head;
    while (current_block != NULL)
    {
        printf("Bloco no endereco %p - %p ---- Tamanho %zu\n", current_block->start, current_block->start + current_block->size, current_block->size);
        current_block = current_block->next;
    }
}

void free_block_display() {
    struct node_s *current_node = list_index(lst, 0);
    free_block *current_free_block = (void *)current_node->data;
    while (current_node->next != NULL)
    {
        current_free_block = (void *)current_node->data;
        printf("Bloco livre no endereco %p ---- Tamanho %zu\n", current_free_block->start, current_free_block->size);
        current_node = current_node->next;
    }
}

// Exibe estatísticas gerais sobre a memória, incluindo:
//      – Número total de alocações
//      – Memória total alocada (em bytes)
//      – Memória total livre (em bytes)
//      – O maior bloco contíguo de memória livre
//      – Número de fragmentos de memória livre (ou seja, blocos de memória entre alocações)
void mymemory_stats(mymemory_t *memory)
{
    if (memory->head == NULL)
    {
        printf("Nenhum bloco alocado\n");
        return;
    }
    allocation_t *current_block = memory->head;
    int total_allocations = 0;
    int total_allocated_memory = 0;
    int total_free_memory = 0;
    int biggest_free_block = 0;
    int total_free_blocks = 0;
    while (current_block != NULL)
    {
        total_allocations++;
        total_allocated_memory += current_block->size;
        current_block = current_block->next;
    }
    struct node_s *current_node = list_index(lst, 0);
    free_block *current_free_block = (void *)current_node->data;
    while (current_node->next != NULL)
    {
        total_free_blocks++;
        current_free_block = (void *)current_node->data;
        total_free_memory += current_free_block->size;
        if (current_free_block->size - biggest_free_block > 0)
        {
            biggest_free_block = current_free_block->size;
        }
        current_node = current_node->next;
    }
    printf("Total de alocacoes: %d\n", total_allocations);
    printf("Total de memoria alocada: %d\n", total_allocated_memory);
    printf("Total de memoria livre: %d\n", total_free_memory);
    printf("Maior bloco livre: %d\n", biggest_free_block);
    printf("Total de blocos livres: %d\n", total_free_blocks);
}