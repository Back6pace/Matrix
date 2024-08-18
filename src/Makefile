GCC_FLAGS = -Wall -Wextra -Werror
SANITAIZER = -g -fsanitize=address
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
EXE=test.out

# Папки поиска
SRC_DIRS = .
OBJ_DIR = ./objs
TEST_DIR = ./tests
TEST_OBJ_DIR = ./tests/objs
BUILD_PATH = gcov_report/
REPORT_PATH = $(BUILD_PATH)report/
TEST_C_FILES := $(wildcard $(TEST_DIR)/test_*.c)


# Поиск всех файлов .c во всех SRC_DIRS
SRC_C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Создание списка объектных файлов, сохраняя структуру директорий
OBJS_C_FILES := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_C_FILES))

# Создание списка объектных файлов для тестов
OBJS_TEST_FILES := $(patsubst %.c, $(TEST_OBJ_DIR)/%.o, $(notdir $(TEST_C_FILES)))
OS := $(shell uname)

ifeq ($(OS),Linux)
	OPEN = xdg-open
	TEST_FLAGS = -lcheck -lsubunit -lrt -lm -pthread
endif
ifeq ($(OS),Darwin)
	OPEN = open
	TEST_FLAGS = -lcheck
endif

all: s21_matrix.a test

rebuild: clean build

build: clean
	gcc $(GCC_FLAGS) -o ${EXE} $(SRC_C_FILES) $(TEST_C_FILES) $(TEST_FLAGS)


s21_matrix.a: $(OBJS_C_FILES)
	ar rcs s21_matrix.a $(OBJS_C_FILES)
	ranlib s21_matrix.a

test: $(TEST_OBJ_DIR)/test_main.o $(OBJS_TEST_FILES) s21_matrix.a
	gcc  $^ $(TEST_FLAGS) -o $(EXE)
	./$(EXE)

# Компиляция исходных файлов в объектные
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	gcc $(GCC_FLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: %.c | $(TEST_OBJ_DIR)
	mkdir -p $(dir $@)
	gcc $(GCC_FLAGS) -c $< -o $@

#Компиляция исходных файлов в объектные для тестов
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(TEST_OBJ_DIR)
	gcc $(GCC_FLAGS) -c $< -o $@

# Создание директории для объектных файлов, если она не существует
$(OBJ_DIR) $(TEST_OBJ_DIR):
	mkdir -p $@

gcov_report: build_dir
	mkdir -p $(REPORT_PATH)
	gcc $(GCC_FLAGS) --coverage $(SRC_C_FILES) $(TEST_C_FILES) -o $(BUILD_PATH)$(EXE) $(TEST_FLAGS)
	chmod +x $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)
	lcov -t "Report" --directory . --capture --output-file $(BUILD_PATH)coverage.info --ignore-errors empty --no-external
	genhtml $(BUILD_PATH)coverage.info --output-directory $(REPORT_PATH)
	$(OPEN) $(REPORT_PATH)index.html

build_dir:
	mkdir -p $(BUILD_PATH)

clean:
	rm -rf $(OBJ_DIR) $(TEST_OBJ_DIR) s21_matrix.a $(EXE) *.out *.gc* *.info $(BUILD_PATH)


docker_build:
	cp ../materials/linters/.clang-format ./
	docker build -t vault:v1 .
	docker create -it --name matrix_vault vault:v1

docker_start:
	docker start -i matrix_vault

docker_delete:
	docker rm matrix_vault
	docker image rm vault:v1

valgrind: rebuild
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks_log.txt ./test.out
	echo --- Valgrind summary --- && cat leaks_log.txt | grep 'total heap usage' && cat leaks_log.txt | grep 'ERROR SUMMARY' 

style_test:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm .clang-format

format_style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm .clang-format