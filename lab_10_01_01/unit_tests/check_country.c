#include "check_country.h"

START_TEST(test_counrty_io_correct)
{
    country_t exp;
    exp.name = "Brazil";
    exp.capital = "Brazil";
    exp.gdp = 2000;
    exp.population = 2000;
    FILE *f = tmpfile();
    print_country(f, &exp);
    rewind(f);

    country_t prod;
    prod.name = NULL;
    prod.capital = NULL;
    prod.gdp = 0;
    prod.population = 0;
    int rc = read_country(f, &prod);
    fclose(f);

    ck_assert_int_eq(rc, OK);
    ck_assert_str_eq(exp.name, prod.name);
    ck_assert_str_eq(exp.capital, prod.capital);
    ck_assert_double_eq_tol(prod.gdp, exp.gdp,1e-8);
    ck_assert_int_eq(exp.population, prod.population);
    free(prod.name);
    free(prod.capital);
}
END_TEST

START_TEST(test_counrty_io_neg_gdp)
{
    country_t exp;
    exp.name = "Brazil";
    exp.capital = "Brazil";
    exp.gdp = -2000;
    exp.population = 2000;
    FILE *f = tmpfile();
    print_country(f, &exp);
    rewind(f);

    country_t prod;
    prod.name = NULL;
    prod.capital = NULL;
    prod.gdp = 0;
    prod.population = 0;
    int rc = read_country(f, &prod);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_NUM_VALUE);
}
END_TEST

START_TEST(test_counrty_io_neg_pop)
{
    country_t exp;
    exp.name = "Brazil";
    exp.capital = "Brazil";
    exp.gdp = 2000;
    exp.population = -2000;
    FILE *f = tmpfile();
    print_country(f, &exp);
    rewind(f);

    country_t prod;
    prod.name = NULL;
    prod.capital = NULL;
    prod.gdp = 0;
    prod.population = 0;
    int rc = read_country(f, &prod);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_NUM_VALUE);
}
END_TEST

START_TEST(test_counrty_io_no_capital)
{
    country_t exp;
    exp.name = "Brazil";
    exp.capital = "Brazil";
    exp.gdp = -2000;
    exp.population = 2000;
    FILE *f = tmpfile();
    fprintf(f, "%s\n%lf\n%d\n", exp.name, exp.gdp, exp.population);
    rewind(f);

    country_t prod;
    prod.name = NULL;
    prod.capital = NULL;
    prod.gdp = 0;
    prod.population = 0;
    int rc = read_country(f, &prod);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_UNABLE_TO_READ_NUMS);
}
END_TEST

START_TEST(test_counrty_io_no_pop)
{
    country_t exp;
    exp.name = "Brazil";
    exp.capital = "Brazil";
    exp.gdp = -2000;
    exp.population = 2000;
    FILE *f = tmpfile();
    fprintf(f, "%s\n%s\n%lf\n", exp.name, exp.capital, exp.gdp);
    rewind(f);

    country_t prod;
    prod.name = NULL;
    prod.capital = NULL;
    prod.gdp = 0;
    prod.population = 0;
    int rc = read_country(f, &prod);
    fclose(f);

    ck_assert_int_eq(rc, ERROR_NUM_VALUE);
}
END_TEST

Suite* country_io_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("country_io");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_counrty_io_correct);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    
    tcase_add_test(tc_neg, test_counrty_io_neg_gdp);
    tcase_add_test(tc_neg, test_counrty_io_neg_pop);
    tcase_add_test(tc_neg, test_counrty_io_no_capital);
    tcase_add_test(tc_neg, test_counrty_io_no_pop);

    suite_add_tcase(s, tc_neg);

    return s;
}

START_TEST(test_country_cmp_equal)
{
    country_t first = {"Germany", "Berlin", 2000, 1};
    country_t second = {"Germany", "Berlin", 2000, 1};

    int cmp = compar_countries(&first, &second);

    ck_assert_int_eq(cmp, 0);
}
END_TEST

START_TEST(test_country_cmp_more)
{
    country_t first = {"Germany", "Berlin", 2000, 1};
    country_t second = {"Algeria", "Algeria", 2000, 1};

    int cmp = compar_countries(&first, &second);

    ck_assert_int_gt(cmp, 0);
}
END_TEST

START_TEST(test_country_cmp_less)
{
    country_t first = {"Germany", "Berlin", 2000, 1};
    country_t second = {"India", "Deli", 2000, 1};

    int cmp = compar_countries(&first, &second);

    ck_assert_int_le(cmp, 0);
}
END_TEST


Suite* country_cmp_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("country_cmp");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_country_cmp_more);
    tcase_add_test(tc_pos, test_country_cmp_less);
    tcase_add_test(tc_pos, test_country_cmp_equal);


    suite_add_tcase(s, tc_pos);

    return s;
}
