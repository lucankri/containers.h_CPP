CC=g++
FLAGS=-Wall -Werror -Wextra -std=c++17 -pedantic -pthread
TESTFLAGS=-lgtest

all: clean test gcov_report

.PHONY: all clean test gcov_report

test: 
	$(CC) --coverage $(FLAGS) ./tests/*.cpp $(TESTFLAGS) -o test
	./test

gcov_report: test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report.html report.info
	rm *.gcda *.gcno
	open report.html/index.html 2>/dev/null

clean:
	rm -rf *.o test
	rm -rf *.gcda *.gcno report.html *.info
	rm -rf .clang-format

check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.h
	cppcheck --language=c++ *.h
