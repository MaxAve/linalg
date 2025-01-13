/*
 * Multiplying a 4x4 matrix with a 4-element vector
 */

#include "../linalg.h"

int main() {
    srand(time(NULL));

	Mat A = laMatNew(3, 2);
	Mat B = laMatNew(2, 3); 
	Mat C = laMatNew(3, 3);

	// Set every value in matrix A to a whole number between 0 and 10
	for(int row = 0; row < A.rows; row++) {
		for(int col = 0; col < A.cols; col++) {
			laMatSet(round(randf(0, 10)), A, row, col);
		}
	}

	// Set every value in matrix B to a whole number between 0 and 10
	for(int row = 0; row < B.rows; row++) {
		for(int col = 0; col < B.cols; col++) {
			laMatSet(round(randf(0, 10)), B, row, col);
		}
	}

	laMatMul(A, B, C); // C = A x B

	laMatPrint(A);
	laMatPrint(B);
	laMatPrint(C);

    return 0;
}
