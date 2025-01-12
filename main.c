#include "linalg.h"

int main() {
    srand(time(NULL));

	Mat4 A = NEW_MAT4;
	Vec4 B = NEW_VEC4; 
	Vec4 C = NEW_VEC4;

	MATSET(1, &A, 0, 0);
	MATSET(2, &A, 1, 0);
	MATSET(3, &A, 2, 0);
	MATSET(4, &A, 3, 0);
	MATSET(1, &A, 0, 1);
	MATSET(2, &A, 1, 1);
	MATSET(3, &A, 2, 1);
	MATSET(4, &A, 3, 1);
	MATSET(1, &A, 0, 2);
	MATSET(2, &A, 1, 2);
	MATSET(3, &A, 2, 2);
	MATSET(4, &A, 3, 2);
	MATSET(1, &A, 0, 3);
	MATSET(2, &A, 1, 3);
	MATSET(3, &A, 2, 3);
	MATSET(4, &A, 3, 3);


	MATSET(1, &B, 0, 0);
	MATSET(2, &B, 1, 0);
	MATSET(3, &B, 2, 0);
	MATSET(4, &B, 3, 0);
	//MATSET(3, &B, 0, 1);
	//MATSET(4, &B, 1, 1);

	mat4vecmul(&A, &B, &C);

    PRINT_MAT(&A);
    printf("\n");
    PRINT_MAT(&B);
    printf("\n");
    PRINT_MAT(&C);

    return 0;
}
