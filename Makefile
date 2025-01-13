all:
	gcc examples/matadd.c -o bin/matadd -lm
	gcc examples/matmul.c -o bin/matmul -lm
	gcc examples/transform.c -o bin/transform -lm
