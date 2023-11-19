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

// Aloca o bloco de memória total e retorna um ponteiro para ele
mymemory_t* mymemory_init(size_t size);

// Tenta alocar um bloco de mem´oria de tamanho especificado. Se a alocação for bem-sucedida, 
// retorna um ponteiro para o in´ıcio do bloco. Caso contrário, retorna NULL.
void* mymemory alloc(mymemory t *memory, size t size);

// Libera a alocação apontada por ptr. Se ptr não for uma alocação válida, a função
// não deve fazer nada.
void mymemory free(mymemory t *memory, void *ptr);

// Exibe todas as alocações atuais, incluindo o início e o tamanho de cada alocação
void mymemory display(mymemory t *memory);

// Exibe estatísticas gerais sobre a memória, incluindo:
//      – Número total de alocações
//      – Memória total alocada (em bytes)
//      – Memória total livre (em bytes)
//      – O maior bloco contíguo de memória livre
//      – Número de fragmentos de mem´oria livre (ou seja, blocos de memória entre alocações)
void mymemory stats(mymemory t *memory);

// Libera todos os recursos (incluindo todas as alocações e o bloco de memória total)
void mymemory cleanup(mymemory t *memory);