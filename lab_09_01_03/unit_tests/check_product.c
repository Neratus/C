#include "check_product.h"
#include <stdlib.h>

START_TEST(test_prod_io_correct)
{
    product_t exp;
    exp.name = "Apple";
    exp.price = 2000;
    FILE *f = tmpfile();
    print_product(f, &exp);
    rewind(f);

    product_t prod;
    prod.name = NULL;
    prod.price = 0;
    int rc = read_product(f, &prod);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_str_eq(exp.name, prod.name);
    ck_assert_int_eq(exp.price, prod.price);
    free(prod.name);
}
END_TEST

START_TEST(test_prod_io_neg_price)
{
    product_t exp;
    exp.name = "Apple";
    exp.price = -2000;
    FILE *f = tmpfile();
    print_product(f, &exp);
    rewind(f);

    product_t prod;
    prod.name = NULL;
    prod.price = 0;
    int rc = read_product(f, &prod);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_PRICE_VALUE);
}
END_TEST

START_TEST(test_prod_io_no_price)
{
    product_t exp;
    exp.name = "Apple";
    exp.price = 2000;
    FILE *f =  tmpfile();
    fprintf(f, "%s\n", exp.name);
    rewind(f);

    product_t prod;
    prod.name = NULL;
    prod.price = 0;
    int rc = read_product(f, &prod);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_UNABLE_TO_READ_NUMS);
}
END_TEST

Suite* product_io_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("prod_io");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_prod_io_correct);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_prod_io_no_price);
    tcase_add_test(tc_neg, test_prod_io_neg_price);

    suite_add_tcase(s, tc_neg);

    return s;
}
