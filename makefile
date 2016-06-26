bin/general_helper_test: bin/general_helper
	gcc `pkg-config --cflags cmockery2` src/unit_test/general_helper_test.c \
	 	-o bin/general_helper_test bin/general_helper `pkg-config --libs cmockery2`

bin/general_helper:
	gcc -O3 -c src/source/general_helper.c -o bin/general_helper

clean:
	rm -r bin/*

all:
	make clean
	make
