bin/general_list_test: bin/general_list bin/general_helper bin/gl_helper bin/general_helper_test
	gcc `pkg-config --cflags cmockery2` src/unit_test/general_list_test.c \
	 	-o bin/general_list_test bin/general_helper `pkg-config --libs cmockery2`

bin/general_helper_test: bin/general_helper
	gcc `pkg-config --cflags cmockery2` src/unit_test/general_helper_test.c \
	 	-o bin/general_helper_test `pkg-config --libs cmockery2`

bin/gl_helper:
			gcc -O3 -c src/source/gl_helper.c -o bin/gl_helper

bin/general_list:
	gcc -O3 -c src/source/general_list.c -o bin/general_list

bin/general_helper:
	gcc -O3 -c src/source/general_helper.c -o bin/general_helper

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
