#ifndef TEST_H
#define TEST_H

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../src/s21_matrix.h"

Suite* test_sum();
Suite* test_sub();
Suite* test_create();
Suite* test_eq();
Suite* test_mul_num();
Suite* test_mul_matrix();
Suite* test_transpose();
Suite* test_dtr();
Suite* test_calc_compl();
Suite* test_invert_matrix();
double get_rand(double min, double max);
#endif  // SRC_TESTS_ME_H
