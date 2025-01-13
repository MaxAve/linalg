/*
 * Adding two 7x7 matrices
 */

#include "../linalg.h"

int main() {
    srand(time(NULL));
    
    Mat A = laMatNew(7, 7);
	Mat B = laMatNew(7, 7);
	Mat C = laMatNew(10, 7);

	// Set every value in matrix A and B to a whole number between -5 and 5 
	for(int row = 0; row < A.rows; row++) {
		for(int col = 0; col < A.cols; col++) {
			laMatSet(round(randf(-5, 5)), A, row, col);
            laMatSet(round(randf(-5, 5)), B, row, col);
		}
	}

    // C = A + B
    laMatAdd(A, B, C);
	
    // You can use safe functions for debugging and error handling
    // Note: you can only run safe functions on arbitrary Mat's (no Mat4's or Vec4's)
    // if(laMatSafeAdd(A, B, C) != 0) {
    //     printf("Cancelled operation due to error :(\n");
    //     return -1;
    // }

	laMatPrint(A);
	laMatPrint(B);
	laMatPrint(C);

    return 0;
}
