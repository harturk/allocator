// Estrutura de alocação, onde indica o ínicio do ponteiro da estrutura alocada, tamanho de sua alocação
// e um ponteiro para a próxima estrutura alocada.
typedef struct allocation {
    void *start;
    size_t size;
    struct allocation *next;
} allocation_t;

// Essa estrutura está referenciando referências para o armazenamento total
typedef struct {
    void *pool;
    size_t total_size;
    allocation_t *head;
} mymemory_t