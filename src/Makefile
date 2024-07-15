CC = gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra --coverage
COV = --coverage
SRC=s21_matrix.c
TESTS=../tests/*.c
FLAG_TEST=-lcheck -lm #-lsubunit
SRCS=$(wildcard s21_*.c)
OBJS=$(SRCS:.c=.o)

all : gcov

format:
	clang-format -n -style=Google $(SRC)
	clang-format -i -style=Google $(SRC)

s21_matrix.a:$(OBJS)
	@ar -rc s21_matrix.a $^
	@ranlib s21_matrix.a
	@rm -rf *.o

test: clean s21_matrix.a
	@gcc $(CFLAGS) $(TESTS) s21_matrix.a $(FLAG_TEST) -o test -g
	@./test

gcov : clean test
	@gcov $(SRCS) > /dev/null
	@lcov -t "repotsTest" -o s21_matrix.info -c -d . > /dev/null
	@genhtml -o report s21_matrix.info > /dev/null
	@xdg-open ./report/index.html

clean:
	@-rm -rf *.o *.gcno *.gcda *.info  test s21_matrix.a gcov_report report greport a.out *.txt *.dSYM *.gcov

 