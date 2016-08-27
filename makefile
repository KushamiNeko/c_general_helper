bin/general_helper_test: bin/general_helper bin/gl_helper bin/linear_math
	gcc `pkg-config --cflags cmockery2` src/general_helper_test.c \
	 	-o bin/general_helper_test `pkg-config --libs cmockery2`

bin/linear_math:
	gcc -Wall -O3 -c src/linear_math.c -o bin/linear_math

bin/gl_helper:
	gcc -O3 -c src/gl_helper.c -o bin/gl_helper

bin/general_list:
	gcc -Wall -O3 -c src/general_list.c -o bin/general_list

bin/general_helper:
	gcc -Wall -O3 -c src/general_helper.c -o bin/general_helper

clean:
	@if [ $(shell find 'bin' -type d -empty)  ]; then\
		echo 'bin is already clean';\
	else\
		echo 'cleaning bin...';\
		rm -r bin/*;\
	fi

all:
	make clean
	make
