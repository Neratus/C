#include <stdlib.h>
#include "list.h"

node_t *node_create(void *data)
{
    node_t *node;
    node = malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

void node_free(node_t *node)
{
    free(node);
}

void node_print(FILE *f, node_t *node, void (*print)(FILE*, const void*))
{
    print(f, node->data);
}

node_t *list_add_tail(node_t *head, node_t *node)
{
    if (head == NULL)
        return node;
    node_t *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
    return head;
}

void print_list(FILE *f, node_t *head, void (*print)(FILE*, const void*))
{
    node_t *tmp = head;
    while (tmp != NULL)
    {
        node_print(f, tmp, print);
        tmp = tmp->next;
    }
}

void list_free(node_t *head)
{
    node_t *tmp = head;
    node_t *next; 
    while (tmp != NULL)
    {
        next = tmp->next;
        node_free(tmp);
        tmp = next;
    }
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*))
{
    node_t *cur = head;
    while (cur != NULL)
    {
        if (comparator(data, cur->data) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;

    void *data = (*head)->data;
    node_t *tmp = *head;
    *head = (*head)->next;
    node_free(tmp);
    return data;
}

void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*))
{
    node_t *tmp = *head;
    while (tmp != NULL && tmp->next != NULL)
    {
        node_t *cur = tmp;
        while ((cur != NULL) && (cur->next != NULL))
        {
            if (comparator(cur->next->data, tmp->data) == 0)
            {
                node_t *duplicate = cur->next; 
                cur->next = cur->next->next;
                node_free(duplicate);
            }
            else
            {
                cur = cur->next;
            }
        }
        tmp = tmp->next;
    } 
}

void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL || head->next == NULL)
    {
        *back = NULL;
        return;
    }

    node_t *slow = head;
    node_t *fast = head->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }

    *back = slow->next;
    slow->next = NULL;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void*, const void*))
{
    node_t *result = NULL;
    node_t *current = NULL;

    if (*head_a == NULL) 
        result = *head_b;
    if (*head_b == NULL) 
        result = *head_a;
        
    while (*head_a != NULL && *head_b != NULL)
    {
        if (comparator((*head_a)->data, (*head_b)->data) <= 0)
        {
            if (result == NULL)
            {
                result = *head_a;
                current = result;
            }
            else
            {
                current->next = *head_a;
                current = current->next;
            }
            *head_a = (*head_a)->next;
        }
        else
        {
            if (result == NULL)
            {
                result = *head_b;
                current = result;
            }
            else
            {
                current->next = *head_b;
                current = current->next;
            }
            *head_b = (*head_b)->next;
        }
    }

    if (current && (*head_a != NULL))
        current->next = *head_a;
    else if (current && (*head_b != NULL))
        current->next = *head_b;

    *head_a = NULL;
    *head_b = NULL;

    return result;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (head == NULL || head->next == NULL)
        return head;

    node_t *front = head;
    node_t *back;
    front_back_split(front, &back);

    front = sort(front, comparator);
    back = sort(back, comparator);

    return sorted_merge(&front, &back, comparator);
}
