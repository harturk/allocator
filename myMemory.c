#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"
#include "list.h"

static mymemory_t *p;

static struct list_s *lst;

mymemory_t *getMymemory_t()
{
    return p;
}

void update_list(struct node_s *node_block, size_t size)
{
    free_block *block = malloc(sizeof(free_block));
    block = (void *)node_block->data;
    block->size = block->size - size;
    block->start = block->start + size + 1;
    printf("Bloco atualizado no endereço %p ---- Tamanho %d\n", block, block->size);
}

struct node_s *find_next_free_block(size_t size)
{
    // Percorre a lista de blocos livres
    if (lst == NULL || lst->head == NULL)
    {
        printf("Lista de blocos livres vazia\n");
        return NULL;
    }
    printf("Procurando bloco livre\n");
    size_t current_size;
    size_t closest_size;
    // free_block *current_block = malloc(sizeof(free_block));
    free_block *closest_block = malloc(sizeof(free_block));
    struct node_s *current_node;
    struct node_s *closest_node;
    printf("Alocando blocos auxiliares\n");

    current_node = list_index(lst, 0);
    free_block *current_block = malloc(sizeof(free_block));
    current_block = (void *)current_node->data;
    printf("1\n");
    printf("%p\n", current_node);
    printf("%p\n", current_block);
    printf("2\n");
    printf("%d\n", current_block->size);
    printf("3\n");
    current_size = current_block->size;
    printf("4\n");
    if (current_size > size)
    {
        closest_node = current_node;
        closest_block = current_block;
        closest_size = current_size;
    }
    printf("Testando tamanhos iniciais\n");

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
        printf("Nenhum bloco adequado foi encontrado\n");
        return NULL;
    }
    printf("Bloco mais próximo encontrado no endereço %p ---- Tamanho %d\n", closest_block, closest_block->size);
    return closest_node;
}

allocation_t *allocate_block(mymemory_t *pool, size_t size)
{
    if (size > pool->total_size)
    {
        printf("Tamanho do bloco maior que o tamanho total do pool\n");
        return NULL;
    }
    allocation_t *allocation_block = malloc(sizeof(allocation_t));
    if (block == NULL)
    {
        printf("Erro ao alocar bloco\n");
        return NULL;
    }

    printf("Validacoes de tamanho\n");

    // Informações sobre o próximo bloco livre na memória
    struct node_s *next_node = find_next_free_block(size);
    free_block *next_block = malloc(sizeof(free_block));
    next_block = (void *)next_node->data;

    printf("Criados blocos auxiliares\n");

    if (next_node == NULL)
    {
        return NULL;
    }
    allocation_block->start = next_block;
    allocation_block->size = size;
    allocation_block->next = NULL;
    // Insere no head caso ainda não tenha sido alocado algum bloco
    if (pool->head == NULL)
    {
        pool->head = allocation_block;
    }
    printf("Block Criado no endereco %p\n", allocation_block);
    return allocation_block;
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
        printf("Pool Criado no endereco %p --- Tamanho %d\n", p->pool, sizeof(size));
        free_block *current_block = malloc(sizeof(free_block));
        current_block->start = p->pool;
        current_block->end = p->pool + size;
        current_block->size = size;

        lst = list_create();
        list_push(lst, (void *)current_block);
        printf("Lista criada\n");
        return p;
    }

    return p;
}

void *mymemory_alloc(mymemory_t *pool, size_t size)
{
    // Inicializa, caso não tenha sido inicializado ainda.
    if (pool == NULL)
    {
        const int POOL_DEFAULT = 1024;
        printf("pool == NULL, Inicializando pool com valor DEFAULT de %d\n", POOL_DEFAULT);
        pool = mymemory_init(size);
    }

    // FIRST FIT
    return allocate_block(pool, size);
}