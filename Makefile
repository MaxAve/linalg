all:
	gcc examples/matadd.c -o bin/matadd -lm
	gcc examples/matmul.c -o bin/matmul -lm
	gcc examples/rotation.c -o bin/rotation -lm
