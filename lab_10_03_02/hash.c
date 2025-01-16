#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

double rehash_size_cl = 1.2;
int base_size_cl = 40;
double allocate_incr_cl = 1.5;

node_t *create_closed_hash_node(const char *key)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->key = malloc(strlen(key) + 1);
    if (node->key == NULL)
    {
        free(node);
        return NULL;
    }
    strcpy(node->key, key);
    node->next = NULL;
    return node;
}

void free_closed_hash_node(node_t *node)
{
    if (node)
    {
        free(node->key); 
        free(node);
    }
}

static int hash_function(const char *key, size_t table_size)
{
    int hash = 0;
    while (*key)
        hash = (hash << 5) + *key++;
    return (int)((unsigned)hash % table_size);
}

int find_next_simple_cl(int cur)
{
    int next = cur + 1;
    int is_simple = 0;
    while (is_simple == 0)
    {
        int was = 0;
        for (int i = 2; i < (int)(next / 2); i++)
        {
            if (next % i == 0)
            {
                was = 1;
                break;
            } 
        }
        if (was == 0)
            return next;
        next++;
    }
    return next;
}
 
void init_closed_hash_table(hash_table_t *hash_table, int *size) 
{
    int alloc_size = base_size_cl;
    if (size != NULL)
        alloc_size = *size;
    hash_table->table = malloc((unsigned)alloc_size * sizeof(node_t *));
    for (int i = 0; i < alloc_size; i++) 
        hash_table->table[i] = NULL;
    hash_table->keys_count = 0;
    hash_table->table_size = alloc_size;
}

void free_closed_table(hash_table_t *hash_table)
{
    if (hash_table) 
    {
        if (hash_table->table) 
        {
            for (int i = 0; i < hash_table->table_size; i++) 
            {
                node_t *node = hash_table->table[i];
                while (node) 
                {
                    node_t *temp = node;
                    node = node->next;
                    free_closed_hash_node(temp); 
                }
            }
            free(hash_table->table);
        }
        free(hash_table);
    }
}

static void rehash_hash_table(hash_table_t **hash_table_ptr, int new_table_size) 
{
    hash_table_t *old_table = *hash_table_ptr; 
    hash_table_t *new_table = malloc(sizeof(hash_table_t));
    init_closed_hash_table(new_table, &new_table_size);
    for (int i = 0; i < old_table->table_size; i++) 
    {
        if (old_table->table[i] != NULL) 
        {
            node_t *node = old_table->table[i];
            
            while (node) 
            {
                int pos = hash_function(node->key, (unsigned)new_table_size);

                node_t *new_node = create_closed_hash_node(node->key);
                if (!new_node) 
                {
                    free_closed_table(new_table);
                    return;
                }

                new_node->next = new_table->table[pos];
                new_table->table[pos] = new_node;

                node = node->next;
            }
        }
    }
    new_table->keys_count = old_table->keys_count;
    free_closed_table(old_table);
    *hash_table_ptr = new_table;
}

int add_elem_to_table(hash_table_t **hash_table_ptr, const char *key, int num)
{
    if (hash_table_ptr == NULL || *hash_table_ptr == NULL) 
        return ERROR_MEMORY;
    if ((*hash_table_ptr)->keys_count >= rehash_size_cl * (*hash_table_ptr)->table_size) 
        rehash_hash_table(hash_table_ptr, find_next_simple_cl((int)(allocate_incr_cl * (*hash_table_ptr)->table_size)));

    int table_size = (*hash_table_ptr)->table_size;
    int index = hash_function(key, (unsigned)table_size);  

    node_t *current = (*hash_table_ptr)->table[index];
    while (current != NULL) 
    {
        if (strcmp(current->key, key) == 0)
        {
            current->val = num;
            return ERROR_KEY_EXISTS;
        }
        current = (node_t *)current->next;
    }
    node_t *new_node = create_closed_hash_node(key);
    if (!new_node) 
        return ERROR_MEMORY;

    new_node->next = (*hash_table_ptr)->table[index];
    new_node->val = num;
    (*hash_table_ptr)->table[index] = new_node;

    (*hash_table_ptr)->keys_count++;

    return 0;
}

int delete_elem_from_table(hash_table_t *hash_table, const char *key)
{
    int table_size = hash_table->table_size;
    int hash = hash_function(key, (unsigned)table_size); 

    node_t *node = hash_table->table[hash];
    node_t *prev = NULL;

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0) 
        {
            if (prev == NULL)  
                hash_table->table[hash] = node->next; 
            else  
                prev->next = node->next;  
            free_closed_hash_node(node); 
            hash_table->keys_count--;  
            return 0;
        }
        prev = node;
        node = node->next;
    }

    return 1; 
}

node_t *find_node(hash_table_t *hash_table, const char *key)
{
    int table_size = hash_table->table_size;
    int hash = hash_function(key, (unsigned)table_size);

    node_t *node = hash_table->table[hash];
    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)  
            return node;
        node = node->next;  
    }
    return NULL; 
}

node_t *find_max_node(hash_table_t *hash_table)
{
    node_t *max = NULL;
    for (int i = 0; i < hash_table->table_size; i++)
    {
        node_t *node = hash_table->table[i];

        while (node != NULL)
        {
            if ((max == NULL) || (strcmp(node->key, max->key) > 0))
                max = node;
            node = node->next; 
        }
    }
    return max;
}

node_t *find_min_node(hash_table_t *hash_table)
{
    node_t *min = NULL;
    for (int i = 0; i < hash_table->table_size; i++)
    {
        node_t *node = hash_table->table[i];

        while (node != NULL)
        {
            if ((min == NULL) || (strcmp(node->key, min->key) < 0))
                min = node;
            node = node->next; 
        }
    }
    return min;
}
