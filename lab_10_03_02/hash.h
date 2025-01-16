#ifndef HASH_H
#define HASH_H

#include <stdio.h>

typedef struct
{
    char *key;
    int val;
    void *next;
}node_t;

typedef struct
{
    node_t **table;
    int keys_count;
    int table_size;
}hash_table_t;

#define ERROR_KEY_EXISTS -1
#define ERROR_MEMORY -2

node_t *create_hash_node(char *name, int val);

void free_hash_node(node_t *node);

void init_closed_hash_table(hash_table_t *hash_table, int *size);

void free_closed_table(hash_table_t *hash_table);

int add_elem_to_table(hash_table_t **hash_table_ptr, const char *key, int num);

int delete_elem_from_table(hash_table_t *hash_table, const char *key);

node_t *find_node(hash_table_t *hash_table, const char *key);

node_t *find_max_node(hash_table_t *hash_table);

node_t *find_min_node(hash_table_t *hash_table);

#endif
