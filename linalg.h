/*
 * MIT License
 *
 * Copyright (c) 2024 MaxAve@github.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#ifndef LINALG_H
#define LINALG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define PI   3.14159265359
#define PI_2 6.28318530718

#define laMatGet(mat, row, col) ((mat).data[(col) * (mat).cols + (row)])
#define laMatGetRaw(data, row, col, cols) (data[(col) * (cols) + (row)])
#define laMatSet(x, mat, row, col) ((mat).data[(col) * (mat).cols + (row)] = (x))
#define laMatSetRaw(x, data, row, col, cols) (data[(col) * (cols) + (row)] = (x))

/*
 * Utilities
 */

float randf(float vmin, float vmax) {
    return (float)rand()/(float)(RAND_MAX/(vmax - vmin))+vmin;
}

float deg2rad(float deg) {
    return deg / 180.0f * PI;
}

float rad2deg(float deg) {
    return deg / PI * 180.0f;
}

/*
 * Struct definitions
 */

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[2];
} Vec2;

#define laVec2Empty (Vec2){2, 1, {.0f, .0f}}
#define laVec2New(x, y) (Vec2){2, 1, {(x), (y)}}
#define VEC2(x, y) (Vec2){2, 1, {(x), (y)}}

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[3];
} Vec3;

#define laVec3Empty (Vec3){3, 1, {.0f, .0f, .0f}}
#define laVec3New(x, y, z) (Vec3){3, 1, {(x), (y), (z)}}
#define VEC3(x, y, z) (Vec3){3, 1, {(x), (y), (z)}}

#define VEC3_RIGHT    (VEC3(1.0f, 0.0f, 0.0f))
#define VEC3_LEFT     (VEC3(-1.0f, 0.0f, 0.0f))
#define VEC3_UP       (VEC3(0.0f, 1.0f, 0.0f))
#define VEC3_DOWN     (VEC3(0.0f, -1.0f, 0.0f))
#define VEC3_FORWARD  (VEC3(0.0f, 0.0f, 1.0f))
#define VEC3_BACKWARD (VEC3(0.0f, 0.0f, -1.0f))

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[4];
} Vec4;

#define laVec4Empty ((Vec4){4, 1, {.0f, .0f, .0f, .0f}})
#define laVec4New(x, y, z, w) ((Vec4){4, 1, {(x), (y), (z), (w)}})
#define VEC4(x, y, z, w) ((Vec4){4, 1, {(x), (y), (z), (w)}})

#define VEC4_RIGHT    (VEC4(1.0f, 0.0f, 0.0f, 1.0f))
#define VEC4_LEFT     (VEC4(-1.0f, 0.0f, 0.0f, 1.0f))
#define VEC4_UP       (VEC4(0.0f, 1.0f, 0.0f, 1.0f))
#define VEC4_DOWN     (VEC4(0.0f, -1.0f, 0.0f, 1.0f))
#define VEC4_FORWARD  (VEC4(0.0f, 0.0f, 1.0f, 1.0f))
#define VEC4_BACKWARD (VEC4(0.0f, 0.0f, -1.0f, 1.0f))

typedef struct {
    unsigned char rows;
    unsigned char cols;
    float* data;
} Mat; 

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[4];
} Mat2;

#define laMat2Empty (Mat2){2, 2, {.0f, .0f, .0f, .0f}}
#define MAT2 laMat2Empty

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[9];
} Mat3;

#define laMat3Empty (Mat3){3, 3, {.0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f}
#define MAT3 laMat3Empty

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[16];
} Mat4;

// Empty Mat4
#define laMat4Empty (Mat4){4, 4, {.0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f}}
#define MAT4 laMat4Empty

/*
 * Operations
 */

void matscale(float* data, int rows, int cols, float scalar) {
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) { // C++?? In MY library??? OUTRAGEOUS!
			laMatSetRaw(laMatGetRaw(data, r, c, cols) * scalar, data, r, c, cols);
		}
	}
}

#define laMatScale(mat, scalar) (matscale((mat).data, (mat).rows, (mat).cols, (scalar)))

Vec4 laVec4Scale(const Vec4 vec, float scalar, bool ignore_w) {
	Vec4 newvec;
	newvec.rows = 4;
	newvec.cols = 1;
	if(ignore_w) {
		for(int i = 0; i < 3; i++) {
			newvec.data[i] = vec.data[i] * scalar;
		}
		newvec.data[3] = vec.data[3];
	} else {
		for(int i = 0; i < 4; i++) {
			newvec.data[i] = vec.data[i] * scalar;
		}
	}
	return newvec;
}

float veclen(const float* data, int rows) {
    float square_sum;
    for(int i = 0; i < rows; i++) {
		float x = laMatGetRaw(data, i, 0, 1);
        square_sum += x*x;
    }
    return sqrt(square_sum);
}

#define laVecLen(vec) veclen(vec.data, vec.rows)

float norm(float* data, int rows) {
    const float vl = veclen(data, rows);
    for(int i = 0; i < rows; i++) {
        laMatSetRaw(laMatGetRaw(data, i, 0, 1) / vl, data, i, 0, 1);
    }
}

#define laVecNormalize(vec) norm(vec.data, vec.rows)

/*
 * Returns a 4x4 rotation matrix for rotating around the vector [R] by the angle [angle]
 * @param R rotation axis (needs to be normalized before calling the function to get expected results)
 * @param angle rotation angle (radians)
 */
Mat4 laMat4GetRotation(Vec3 R, float angle) {
    const float x=R.data[0], y=R.data[1], z=R.data[2];
    const float sinang = sin(angle);
    const float cosang = cos(angle);
    return (Mat4){4, 4, {
        cosang + x*x * (1 - cosang),    x*y * (1 - cosang) + z * sinang,    z * x * (1 - cosang) - y * sinang,  0,
        x*y*(1 - cosang) - z * sinang,  cosang + y*y * (1 - cosang),        z * y * (1 - cosang) + x * sinang,  0,
        x*z*(1 - cosang) + y * sinang,  y*z*(1 - cosang) - x*sinang,        cosang + z*z*(1 - cosang),          0,
        0,                              0,                                  0,                                  1 
    }};
}

Mat4 laMat4GetTranslation(Vec3 tf) {
    return (Mat4){4, 4, {
        1, 			0, 			0,			0, 
        0, 			1, 			0,			0,
        0, 			0, 			1,			0,
        tf.data[0], tf.data[1], tf.data[2], 1
    }};
}

void printmat(const float* data, int rows, int cols) {
    printf("[");
    for(int i = 0; i < rows; i++) {
        if(i > 0)
            printf(" ");
        for(int j = 0; j < cols; j++) {
            float v = laMatGetRaw(data, i, j, cols);
            if(v >= 0)
                printf(" ");
            printf("%0.4f", v);
            if(j < cols - 1)
                printf("  ");
        }
        if(i < rows-1)
            printf("\n");
    }
    printf("]\n");
}

#define laMatPrint(mat) printmat((mat).data, (mat).rows, (mat).cols)

void matfill(float val, float* mat, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("(%i, %i)", i, j);
			laMatSetRaw(val, mat, i, j, cols);
        }
    }
}

#define laMatFill(mat, x) matfill(x, mat.data, mat.rows, mat.cols)

void matadd(const float *A, int arows, int acols, const float *B, int brows, int bcols, float *C) {
    for(int i = 0; i < arows; i++) {
        for(int j = 0; j < acols; j++) {
        	laMatSetRaw(laMatGetRaw(A, i, j, acols) + laMatGetRaw(B, i, j, bcols), C, i, j, acols);
		}
    }
}

#define laMatAdd(A, B, C) matadd((A).data, (A).rows, (A).cols, (B).data, (B).rows, (B).cols, (C).data)

int matsafeadd(const Mat* A, const Mat* B, Mat* C) {
    if(A->rows != B->rows || A->cols != B->cols || B->rows != C->rows || B->cols != C->cols) {
        printf("[ERROR] linalg:laMatSafeAdd -> matrix sizes do not match (%i, %i), (%i, %i), (%i, %i)\n", A->rows, A->cols, B->rows, B->cols, C->rows, C->cols);
        return -1;
    }
    laMatAdd(*A, *B, *C);
    return 0;
}

#define laMatSafeAdd(A, B, C) matsafeadd(&A, &B, &C)

void matmul(const float *A, int arows, int acols,
			const float *B, int brows, int bcols,
			float *C, int ccols) {
	for(int ar = 0; ar < arows; ar++) {
		for(int bc = 0; bc < bcols; bc++) {
			float sum = 0.0f;
			for(int i = 0; i < acols; i++) {
				sum += laMatGetRaw(A, ar, i, acols) * laMatGetRaw(B, i, bc, bcols);
			}
			laMatSetRaw(sum, C, ar, bc, ccols);
		}
	}
}

#define laMatMul(A, B, C) matmul((A).data, (A).rows, (A).cols, (B).data, (B).rows, (B).cols, (C).data, (C).cols)

int matsafemul(const Mat* A, const Mat* B, Mat* C) {
    if(A->cols != B->rows) {
        printf("[ERROR] linalg:laMatSafeMul -> matrix sizes do not match (%i, %i), (%i, %i), (%i, %i). Expected: (%i, %i), (%i, %i), (%i, %i)\n", A->rows, A->cols, B->rows, B->cols, C->rows, C->cols, A->rows, A->cols, A->cols, B->rows, 0, 0);
        return -1;
    }
    laMatMul(*A, *B, *C);
    return 0;
}

#define laMatSafeMul(A, B, C) matsafemul(&A, &B, &C)

/**
 * Multiply two Mat4's. This method is preffered over laMatMul when
 * working specifically with the above mentioned transformation
 */
Mat4 laTransformMat4(const Mat4* A, const Mat4* B) {
	Mat4 C;
	C.rows = 4;
	C.cols = 4;
	
	for(int ar = 0; ar < 4; ar++) {
		for(int bc = 0; bc < 4; bc++) {
			float sum = 0.0f;
			for(int i = 0; i < 4; i++) {
				sum += A->data[i * 4 + ar] * B->data[bc * 4 + i];
			}
			C.data[bc * 4 + ar] = sum;
		}
	}

	return C;
}

/**
 * Multiply a Mat4 by a Vec4. This method is preffered over laMatMul when
 * working specifically with the above mentioned transformation
 */
Vec4 laTransformVec4(const Mat4* A, const Vec4* B) {
	Vec4 C;
	C.rows = 4;
	C.cols = 1;
	
	for(int ar = 0; ar < 4; ar++) {
		float sum = 0.0f;
		for(int i = 0; i < 4; i++) {
			sum += A->data[i * 4 + ar] * B->data[i];
		}
		C.data[ar] = sum;
	}

	return C;
}

/*
 * Arbitrary Mat's
 */

Mat laMatNew(int rows, int cols) {
    Mat mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (float*)malloc(sizeof(float) * rows * cols);
    return mat;
}

void laMatFree(Mat* mat) {
	mat->rows = 0;
	mat->cols = 0;
	free(mat->data);
	mat->data = NULL;
}

#endif
