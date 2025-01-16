#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

static node_t *create_node(void *data)
{
    node_t *cur = malloc(sizeof(node_t));
    if (cur == NULL)
        return NULL;
    cur->data = data;
    cur->next = NULL;
    return cur;
}

static void node_free(node_t *node)
{
    free(node->data);
    free(node);
}

static void print_node(FILE *f, node_t *node)
{
    fprintf(f, "%s \n",(char *)node->data);
}

void print_list(char *file, node_t *head)
{
    FILE *f = fopen(file, "w");
    if (f == NULL)
        return;
    node_t *tmp = head;
    while(tmp != NULL)
    {
        print_node(f, tmp);
        tmp = tmp->next;
    }
    fclose(f);
}

void free_list(node_t *head)
{
    node_t* tmp = head;
    node_t* next; 
    while(tmp != NULL)
    {
        next = tmp->next;
        node_free(tmp);
        tmp = next;
    }
}

node_t *list_add(node_t *head, node_t *node)
{
    if (head == NULL)
        return node;
    node_t *cur = head;
    while(cur->next != NULL)
        cur = cur->next;
    cur->next = node;
    return head;
}

void* pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;

    void *data = (*head)->data;
    node_t *tmp = *head;
    *head = (*head)->next;

    node_free(tmp);
    return data;
}

int init_list(char *file_path, node_t **node)
{
    FILE *f = fopen(file_path, "r");
    if (f == NULL)
        return ERROR_FILE;
    
    char *cur = NULL;
    size_t len;
    while(getline(&cur, &len, f) != -1)
    {
        cur[strcspn(cur, "\n")] = 0;

        if (strspn(cur, " \t \n") == strlen(cur))
            continue;
        
        node_t *temp = create_node(strdup(cur));
        if (temp == NULL)
        {
            free(cur);
            free_list(*node);
            fclose(f);
            return ERROR_MALLOC;
        }
        *node = list_add(*node, temp);
    }
    fclose(f);
    free(cur);
    return OK; 
}

void split_list(node_t **head)
{
    node_t *cur = *head;
    
    size_t cnt = 0;
    while(cur != NULL)
    {
        cnt++;
        cur = cur->next;
    }
    cur = *head;

    for (size_t i = 0; i < cnt; i++)
    {

        char *str = cur->data;
        char *process = strdup(str);

        char *first = strtok (process," \t\n");
        char *next = strtok (NULL," \t\n");

        if (next == NULL)
        {
            for (size_t j = 0; first[j] != '\0'; j++)
            {
                if (first[j] == ' ')
                    continue;

                char *word = malloc(2 * sizeof(char));
                word[0] = first[j];
                word[1] = '\0';

                *head = list_add(*head, create_node(strdup(word)));
                free(word);
            }
        }
        else
        {
            *head = list_add(*head, create_node(strdup(first)));

            while(next != NULL)
            {
                *head = list_add(*head, create_node(strdup(next)));
                next = strtok (NULL," \t\n");
            }
            
        }

        free(process);
        cur = cur->next;
    }

    for (size_t i = 0; i < cnt; i++)
        pop_front(head);
    
    return;
}
