ifeq ($(BUILD),debug)
	FLAGS = -Og -Wall -g -DDEBUG
else
	FLAGS = -O3 -Wall -Werror -s -DNDEBUG
endif

GENERAL_HELPER = ~/programming_projects/c/general/bin

TEST_PKG_CONFIG_LIBS = cmockery2

#bin/linear_math_test: bin/linear_math
#	gcc $(FLAGS) `pkg-config --cflags cmockery2` src/general_helper_test.c \
	#		-o bin/general_helper_test `pkg-config --libs cmockery2`

all: bin/general_helper bin/general_helper_test bin/linear_math bin/gl_helper bin/obj_parser

bin/general_helper_test: bin/general_helper
	gcc $(FLAGS) `pkg-config --cflags $(TEST_PKG_CONFIG_LIBS)` src/general_helper_test.c \
		-o bin/general_helper_test `pkg-config --libs $(TEST_PKG_CONFIG_LIBS)`

bin/linear_math:
	gcc $(FLAGS) -c src/linear_math.c -o bin/linear_math

bin/gl_helper:
	gcc $(FLAGS) -c src/gl_helper.c -o bin/gl_helper

bin/obj_parser:
	gcc $(FLAGS) -c src/obj_parser.c -o bin/obj_parser

bin/general_helper:
	gcc $(FLAGS) -c src/general_helper.c -o bin/general_helper

clean:
	rm -f bin/*

release:
	make clean
	make

debug:
	make clean
	make "BUILD=debug"

test:
	make debug
	bin/general_helper_test
