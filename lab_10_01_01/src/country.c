#include "country.h"

int read_str(char **dest, size_t *len, FILE *f)
{
    if (getline(dest, len, f) != -1) 
    {
        (*dest)[strcspn(*dest, "\n")] = 0;
        return OK;
    }
    return ERROR_STR_INPUT;
}

int read_country(FILE *f, country_t *country)
{
    char *name = NULL;
    char *capital = NULL;
    size_t len = 0;
    if (read_str(&name, &len, f) == ERROR_STR_INPUT) 
    {
        free(name);
        return ERROR_STR_INPUT;
    }

    if (read_str(&capital, &len, f) == ERROR_STR_INPUT) 
    {
        free(name);
        free(capital);
        return ERROR_STR_INPUT;
    }

    double gdp = -1;
    if (fscanf(f, "%lf ", &gdp) != 1)
    {
        free(name);
        free(capital);
        return ERROR_UNABLE_TO_READ_NUMS;
    }
    if (gdp < 0)
    {   
        free(name);
        free(capital);
        return ERROR_NUM_VALUE;
    }

    int population = -1;
    if (fscanf(f, "%d ", &population) != 1)
    {
        free(name);
        free(capital);
        return ERROR_UNABLE_TO_READ_NUMS;
    }
    if (population < 0)
    {   
        free(name);
        free(capital);
        return ERROR_NUM_VALUE;
    }

    country->name = name;
    country->capital = capital;
    country->gdp = gdp;
    country->population = population;
    return OK;
}

void print_country(FILE *f, const void *country_ptr)
{
    const country_t *country = country_ptr;
    fprintf(f, "%s\n%s\n%lf\n%d\n", country->name, country->capital, country->gdp, country->population);
}

void free_country(country_t country)
{
    free(country.name);
    free(country.capital);
}

void free_countries(country_t *countries, size_t list_cnt)
{
    for (size_t i = 0; i < list_cnt; i++)
        free_country(countries[i]);
    free(countries);
}

int compar_countries(const void *first, const void *second)
{
    const country_t *first_country = first;
    const country_t *second_country = second;
    return strcmp(first_country->name, second_country->name);
}

int read_countries(char *path_to_file, country_t **countries, size_t *list_cnt)
{
    FILE *f = fopen(path_to_file, "r");
    if (f == NULL)
        return ERROR_FILE_PATH;
    
    size_t arr_size = 0;
    unsigned int allocated = BASIC_ALLOC;

    *countries = malloc(sizeof(country_t) * allocated);
    if (*countries == NULL)
    {
        fclose(f);
        return ERROR_MALLOC;
    }
    int rc;
    while ((rc = read_country(f, &(*countries)[arr_size])) == OK)
    {
        arr_size++;
        if (arr_size == allocated)
        {
            allocated *= ALLOC_INCR;
            country_t *new_countries = realloc(*countries, sizeof(country_t) * allocated);

            if (new_countries == NULL)
            {
                free_countries(*countries, arr_size);
                fclose(f);
                return ERROR_MALLOC;
            }
            *countries = new_countries;
        }
    }
    fclose(f);
    
    if ((rc != ERROR_STR_INPUT) && (rc != OK))
    {
        free_countries(*countries, arr_size);
        return rc; 
    }

    *list_cnt = arr_size;
    return OK;
}

