clear: 
	rm -rf *.o *.a *_test

fmt: 
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

quadratic_equation.o: quadratic_equation.c quadratic_equation.h
	gcc -g -c quadratic_equation.c -o quadratic_equation.o -lm

quadratic_equation.a: quadratic_equation.o
	ar rc quadratic_equation.a quadratic_equation.o -lm

quadratic_equation_test.o: quadratic_equation_test.c quadratic_equation.h
	gcc -g -c quadratic_equation_test.c -o quadratic_equation_test.o

quadratic_equation_test: quadratic_equation_test.o quadratic_equation.a 
	gcc -g -static -o quadratic_equation_test quadratic_equation_test.o quadratic_equation.a -lm

integral.o: integral.c integral.h
	gcc -g -c integral.c -o integral.o

integral.a: integral.o
	ar rc integral.a integral.o
	
integral_test.o: integral_test.c
	gcc -g -c integral_test.c -o integral_test.o

integral_test: integral_test.o integral.a 
	gcc -g -static -o integral_test integral_test.o integral.a -lm

test: quadratic_equation_test integral_test
	@for test in $(shell find . -maxdepth 2 -type f -regex '.*_test'); do \
		echo "$$test is running"; \
		./$$test || exit 1; \
	done
