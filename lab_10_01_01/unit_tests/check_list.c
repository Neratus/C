#include "check_list.h"

int init_int_list_from_array(node_t **head, int *int_arr, size_t len)
{
    if (len == 0)
    {
        *head = NULL;
        return OK;
    }
    node_t *tmp;
    tmp = node_create(&int_arr[0]);
    if (tmp == NULL)
        return ERROR_MALLOC;
    *head = tmp;
    for (size_t i = 1; i < len; i++)
    {
        tmp = node_create(&int_arr[i]);
        if (tmp == NULL)
            return ERROR_MALLOC;
        *head = list_add_tail(*head, tmp);
    }
    return OK;
}

int cmp_int(const void *a, const void *b)
{
    return (*(const int*)a) - (*(const int*)b);
}

START_TEST(test_list_add_tail_empty)
{
    node_t *head = NULL;
    node_t *new_node = node_create(NULL);
    head = list_add_tail(head, new_node);

    ck_assert_ptr_eq(head, new_node);

    list_free(head);
}
END_TEST


START_TEST(test_list_add_tail_nonempty)
{
    node_t *head = node_create(NULL);
    node_t *node1 = node_create(NULL);
    node_t *node2 = node_create(NULL);
    
    head->next = node1;
    node1->next = node2;

    node_t *new_node = node_create(NULL);
    head = list_add_tail(head, new_node);

    ck_assert_ptr_eq(head->next->next->next, new_node);

    list_free(head);
}
END_TEST

Suite* list_add_tail_suite(void)
{
    Suite *s;
    TCase *core;

    s = suite_create("list_add_tail");

    core = tcase_create("pos");
    tcase_add_test(core, test_list_add_tail_empty);
    tcase_add_test(core, test_list_add_tail_nonempty);

    suite_add_tcase(s, core);

    return s;
}
START_TEST(test_find_nonempty_list_beg)
{
    int arr[3] = {1, 2, 3};
    size_t n = 3;

    node_t *head;
    ck_assert_int_eq(init_int_list_from_array(&head, arr, n), OK);

    int x = 1;
    node_t *res = find(head, &x, cmp_int);
    ck_assert_ptr_eq(res, head); 

    list_free(head);
}
END_TEST

START_TEST(test_find_nonempty_list_end)
{
    int arr[3] = {1, 2, 3};
    size_t n = 3;

    node_t *head;
    ck_assert_int_eq(init_int_list_from_array(&head, arr, n), OK);

    int x = 3;
    node_t *res = find(head, &x, cmp_int);
    ck_assert_ptr_eq(res, head->next->next);  

    list_free(head);
}
END_TEST

START_TEST(test_find_nonempty_list_mid)
{
    int arr[3] = {1, 2, 3};
    size_t n = 3;

    node_t *head;
    ck_assert_int_eq(init_int_list_from_array(&head, arr, n), OK);

    int x = 2;
    node_t *res = find(head, &x, cmp_int);
    ck_assert_ptr_eq(res, head->next); 

    list_free(head);
}
END_TEST

START_TEST(test_find_nonempty_list_one)
{
    int arr[1] = {1};
    size_t n = 1;

    node_t *head;
    ck_assert_int_eq(init_int_list_from_array(&head, arr, n), OK);

    int x = 1;
    node_t *res = find(head, &x, cmp_int);
    ck_assert_ptr_eq(res, head);  

    list_free(head);
}
END_TEST

START_TEST(test_find_empty_list)
{
    node_t *head = NULL;

    int x = 42;
    node_t *res = find(head, &x, cmp_int);

    ck_assert_ptr_null(res); 
}
END_TEST

Suite* find_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("find");

    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_find_nonempty_list_beg);
    tcase_add_test(tc_pos, test_find_nonempty_list_end);
    tcase_add_test(tc_pos, test_find_nonempty_list_mid);
    tcase_add_test(tc_pos, test_find_nonempty_list_one);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_find_empty_list);

    suite_add_tcase(s, tc_neg);

    return s;
}
