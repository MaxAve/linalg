/*
 * Multiplying a 4x4 matrix with a 4-element vector
 */

#include "../linalg.h"

int main() {
    srand(time(NULL));

	// Note: you don't need to manually free static Mat's (Mat4, Vec4, etc.)
	Mat4 A = laMat4Empty;
	Vec4 B = laVec4Empty;
	Vec4 C = laVec4Empty;
	
	// This works too, but the above approach is recommended when working with matrices of a known size (e.g. 4x4)
	// Mat A = laMatNew(4, 4);
	// Mat B = laMatNew(4, 1); // Vectors are represented as single-column matrices
	// Mat C = laMatNew(4, 1);

	// Set every value in matrix A to a whole number between -5 and 5 
	for(int row = 0; row < A.rows; row++) {
		for(int col = 0; col < A.cols; col++) {
			laMatSet(round(randf(-5, 5)), A, row, col);
		}
	}

	// Set every value in vector B to a whole number between -5 and 5
	for(int row = 0; row < 4; row++) {
		laMatSet(round(randf(-5, 5)), B, row, 0);
	}

	laMatMul(A, B, C); // C = A x B

	laMatPrint(A);
	laMatPrint(B);
	laMatPrint(C);

    return 0;
}
