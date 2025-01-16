#ifndef COUNTRY_LIST_H
#define COUNTRY_LIST_H

#include "country.h"
#include "list.h"

#define ERROR_NOT_FOUND -12

int init_country_list_from_array(node_t **head, country_t *country_arr, size_t len);

node_t *sort_countries_list(node_t *head);

void remove_dupl_countries_list(node_t **head);

country_t *find_countries_list(node_t *head, country_t *search);

country_t *pop_front_countries_list(node_t **head);

void print_countries_list(FILE *f, node_t *head);

int func_sort(char *input, char *output);

int func_delete_dupl(char *input, char *output);

int func_find(char *input, char *output, char *node);

#endif
