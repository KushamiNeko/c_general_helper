bin/general_helper:
	gcc -O3 -c source/general_helper.c -o bin/general_helper

clean:
	rm -r bin/*

build:
	make clean
	make
