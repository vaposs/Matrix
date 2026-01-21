# Основные настройки
CC         := gcc
AR         := ar
ARFLAGS    := rcs

# Директории
CORE_DIR   := .
TEST_DIR   := tests
BUILD_DIR  := build
REPORT_DIR := report

# Имена файлов
LIB_NAME   := s21_matrix.a
TEST_BIN   := $(BUILD_DIR)/test_matrix
GCOV_EXEC  := $(BUILD_DIR)/test_matrix_gcov

# Флаги компиляции
CFLAGS     := -std=c11 -Wall -Wextra -Werror -g

# Проверка системы
UNAME_S    := $(shell uname -s)

# Библиотеки check
CHECK_CFLAGS := $(shell pkg-config --cflags check 2>/dev/null || echo "")
CHECK_LIBS   := $(shell pkg-config --libs check 2>/dev/null || echo "-lcheck")

# Дополнительные флаги линковки
LDFLAGS := -lm -lpthread
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lsubunit
endif

# Исходные файлы
CORE_SRC    := $(wildcard *.c)
TEST_SRC    := $(wildcard $(TEST_DIR)/*.c)

# Объектные файлы
CORE_OBJ    := $(patsubst %.c,$(BUILD_DIR)/%.o,$(CORE_SRC))
TEST_OBJ    := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/$(TEST_DIR)/%.o,$(TEST_SRC))
CORE_OBJ_GCOV := $(patsubst %.c,$(BUILD_DIR)/%_gcov.o,$(CORE_SRC))

# Цели по умолчанию
.PHONY: all lib test clean rebuild format check valgrind valgrind_verbose clean_gcov gcov_report

all: lib

# Сборка библиотеки
lib: $(LIB_NAME)

$(LIB_NAME): $(CORE_OBJ)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Создание библиотеки $@ завершено"

# Компиляция объектных файлов
$(BUILD_DIR)/%.o: %.c s21_matrix.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CHECK_CFLAGS) -c $< -o $@

# Компиляция объектных файлов с покрытием
$(BUILD_DIR)/%_gcov.o: %.c s21_matrix.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CHECK_CFLAGS) -fprofile-arcs -ftest-coverage -c $< -o $@

# Сборка обычных тестов
$(TEST_BIN): $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ) $(LIB_NAME) $(CHECK_LIBS) $(LDFLAGS)

# Сборка тестов с покрытием
$(GCOV_EXEC): $(TEST_OBJ) $(CORE_OBJ_GCOV)
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -o $@ $(TEST_OBJ) $(CORE_OBJ_GCOV) $(CHECK_LIBS) $(LDFLAGS)

# Запуск тестов
test: $(TEST_BIN)
	@./$(TEST_BIN)

# Очистка
clean:
	@echo "Очистка мусора"
	@rm -rf $(BUILD_DIR) $(REPORT_DIR) $(LIB_NAME) *.gcno *.gcda *.gcov coverage*.info $(GCOV_EXEC)
	@echo "Очистка завершена"

clean_gcov:
	@rm -f *.gcno *.gcda *.gcov gcov.* 2>/dev/null || true
	@rm -rf $(REPORT_DIR) 2>/dev/null || true

rebuild: clean all

# Проверка на утечки памяти (macOS версия)
valgrind: $(TEST_BIN)
	@echo "🔍 Проверка на утечки памяти..."
	@leaks -atExit -quiet -- ./$(TEST_BIN)
	

style:
	@echo "🔍 Проверка стиля по школе 21"
	mv ../materials/linters/.clang-format .clang-format
	clang-format -n -style=Google *.c *.h $(TEST_DIR)/*.c $(TEST_DIR)/*.h
	mv .clang-format ../materials/linters/.clang-format
	@echo "🔍 Проверка завершена"

style_fix:
	@echo "🔍 Исправление стиля по школе 21"
	mv ../materials/linters/.clang-format .clang-format
	clang-format -i -style=Google *.c *.h $(TEST_DIR)/*.c $(TEST_DIR)/*.h
	mv .clang-format ../materials/linters/.clang-format
	@echo "🔍 Исправление завершено"



# Отчет о покрытии
gcov_report: clean_gcov $(GCOV_EXEC)
	@echo "1. Запуск тестов с покрытием..."
	@./$(GCOV_EXEC)
	
	@echo "2. Проверка файлов покрытия..."
	@if ls $(BUILD_DIR)/*.gcda 1>/dev/null 2>&1; then \
		echo "✓ Файлы покрытия созданы"; \
	else \
		echo "✗ Файлы покрытия НЕ созданы!"; \
		echo "   Возможно тесты не запустились или завершились с ошибкой"; \
		exit 1; \
	fi
	
	@echo "3. Генерация HTML отчета..."
	@mkdir -p $(REPORT_DIR)
	
	# Используем gcovr с указанием корневой директории
	@gcovr --root . \
	       --exclude="tests/.*" \
	       --html --html-details \
	       -o $(REPORT_DIR)/index.html \
	       --gcov-ignore-errors=source_not_found \
	       2>/dev/null || \
	(gcovr --root . \
	       --exclude="tests/.*" \
	       --html --html-details \
	       -o $(REPORT_DIR)/index.html \
	       --gcov-ignore-errors=source_not_found; \
	 echo "✅ HTML отчет создан: $(REPORT_DIR)/index.html")
	
	@if [ -f "$(REPORT_DIR)/index.html" ]; then \
		echo "✅ HTML отчет создан: $(REPORT_DIR)/index.html"; \
		if command -v open >/dev/null 2>&1; then \
			open $(REPORT_DIR)/index.html 2>/dev/null || true; \
		elif command -v xdg-open >/dev/null 2>&1; then \
			xdg-open $(REPORT_DIR)/index.html 2>/dev/null || true; \
		fi; \
	else \
		echo "❌ Не удалось создать отчет"; \
		echo "   Попробуйте установить gcovr: pip install gcovr"; \
	fi