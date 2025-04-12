clear: 
	rm -rf *.o *.a *_test

fmt: 
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

list.o: list.c list.h
	gcc -g -c list.c -o list.o

list.a: list.o
	ar rc list.a list.o
	
list_test.o: list_test.c list.h
	gcc -g -c list_test.c -o list_test.o

list_test: list_test.o list.a
	gcc -g -static -o list_test list_test.o list.a -lm

test: list_test
	@for test in $(shell find . -maxdepth 2 -type f -regex '.*_test'); do \
		echo "$$test is running"; \
		./$$test || exit 1; \
	done
