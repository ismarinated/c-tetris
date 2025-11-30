OS = $(shell uname -s)

FLAGS = -Wall -Werror -Wextra -std=c11
NCURSES_LIB = -lncurses
TEST_LIB = -lcheck

ifeq ($(OS), Linux)
	TEST_LIB += -lpthread -lrt -lsubunit -lm
else ifeq ($(OS), Darwin)
	TEST_LIB += -lsubunit -lm
endif

SRC = brick_game.c gui/cli/*.c brick_game/tetris/*.c

all: install

brickgame.a:
	mkdir -p build
	gcc $(FLAGS) -c $(SRC)
	ar rcs build/brickgame.a
	mv *.o build

install: clean brickgame.a
	gcc $(SRC) $(NCURSES_LIB) -o build/tetris

uninstall:
	rm -rf build

dvi:
	doxygen Doxyfile

dist:
	tar -czvf brickgame.tar.gz Makefile brick_game gui tests brick_game.c brick_game.h Doxyfile diagram.png

test:
	gcc $(FLAGS) tests/tests.c brick_game/tetris/*.c $(TEST_LIB) -o tests/test
	./tests/test

add_coverage_flag:
	$(eval FLAGS += --coverage)

gcov_report: add_coverage_flag test
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info "*/tests/*" --output-file filtered_coverage.info
	genhtml filtered_coverage.info --output-directory gcov_report
	rm -rf *.gcno *.gcda *.gcov *.html *.css *.info
	rm -rf tests/*.gcno tests/*.gcda

clean:
	rm -rf build docs
	rm -rf *.o *.a tests/test
	rm -rf *.gcno *.gcda *.gcov *.html *.css gcov_report *.info
	rm -rf tests/*.gcno tests/*.gcda
	rm -rf *gz

clean_txt:
	rm -f score.txt

run:
	./build/tetris

check:
ifeq ($(OS),Linux)
	valgrind --tool=memcheck --leak-check=yes ./build/tetris
else
	leaks --atExit -- ./build/tetris
endif

clang-format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.c *.h gui/cli/*.c gui/cli/*.h brick_game/tetris/*.c brick_game/tetris/*.h tests/*.c tests/*.h
	rm -f .clang-format