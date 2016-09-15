ifeq ($(BUILD),debug)
FLAGS = -Og -Wall -g -DDEBUG
else
FLAGS = -O3 -Wall -Werror -s 
endif

GENERAL_HELPER = ~/programming_projects/c/general/bin

#bin/linear_math_test: bin/linear_math
#	gcc $(FLAGS) `pkg-config --cflags cmockery2` src/general_helper_test.c \
#	 	-o bin/general_helper_test `pkg-config --libs cmockery2`

bin/general_helper_test: bin/general_helper bin/linear_math bin/gl_helper
	gcc $(FLAGS) `pkg-config --cflags cmockery2` src/general_helper_test.c \
	 	-o bin/general_helper_test `pkg-config --libs cmockery2`

bin/linear_math:
	gcc $(FLAGS) -c src/linear_math.c -o bin/linear_math

bin/gl_helper:
	gcc $(FLAGS) `pkg-config --cflags glib-2.0` -c src/gl_helper.c -o bin/gl_helper `pkg-config --libs glib-2.0`

bin/general_helper:
	gcc $(FLAGS) -c src/general_helper.c -o bin/general_helper

clean:
	@if [ $(shell find 'bin' -type d -empty)  ]; then\
		echo 'bin is already clean';\
	else\
		echo 'cleaning bin...';\
		rm -r bin/*;\
	fi

release:
	make clean
	make

debug:
	make clean
	make "BUILD=debug"

test: 
	make debug
	bin/general_helper_test
