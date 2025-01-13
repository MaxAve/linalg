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

#define PI 3.14159265359

#define laMatGet(mat, row, col) ((mat).data[(col) * (mat).cols + (row)])
#define laMatGetRaw(data, row, col, cols) (data[(col) * (cols) + (row)])
#define laMatSet(x, mat, row, col) ((mat).data[(col) * (mat).cols + (row)] = (x))
#define laMatSetRaw(x, data, row, col, cols) (data[(col) * (cols) + (row)] = (x))

#define MAT4_ROWS 4
#define MAT4_COLS 4
#define VEC4_ROWS 4
#define VEC4_COLS 1
#define VEC3_ROWS 3
#define VEC3_COLS 1

/*
 * Utilities
 */

float randf(float vmin, float vmax) {
    return (float)rand()/(float)(RAND_MAX/(vmax - vmin))+vmin;
}

/*
 * Struct definitions
 */

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[3];
} Vec3;

#define laVec3Empty (Vec3){VEC3_ROWS, VEC3_COLS, {.0f, .0f, .0f}}
#define laVec3New(x, y, z) (Vec3){VEC3_ROWS, VEC3_COLS, {(x), (y), (z)}}

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[4];
} Vec4;

#define laVec4Empty (Vec4){VEC4_ROWS, VEC4_COLS, {.0f, .0f, .0f, .0f}}

typedef struct {
    unsigned char rows;
    unsigned char cols;
    float* data;
} Mat; 

typedef struct {
	unsigned char rows;
	unsigned char cols;
	float data[16];
} Mat4;

// Empty Mat4
#define laMat4Empty (Mat4){MAT4_ROWS, MAT4_COLS, {.0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f}}

/*
 * Operations
 */

float veclen(const float* data, int rows) {
    float square_sum;
    for(int i = 0; i < rows; i++) {
        square_sum += laMatGetRaw(data, i, 0, 1);
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

Mat4 laMat4Rotation(const Vec3* R, float angle) {
    const float x=R->data[0], y=R->data[1], z=R->data[2];
    const float sinang = sin(angle);
    const float cosang = cos(angle);
    return (Mat4){MAT4_ROWS, MAT4_COLS, {
        cosang + x*x * (1 - cosang),    x*y * (1 - cosang) + z * sinang,    z * x * (1 - cosang) - z * sinang,  0,
        x*y*(1 - cosang) - z * sinang,  cosang + y*y * (1 - cosang),        z * y * (1 - cosang) + x * sinang,  0,
        x*z*(1 - cosang) + y * sinang,  y*z*(1 - cosang) - x*sinang,        cosang + z*z*(1 - cosang),          0,
        0,                              0,                                  0,                                  1 
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

void matmul(const float *A, int arows, int acols, const float *B, int brows, int bcols, float *C, int ccols) {
    for(int i = 0; i < brows; i++) {
        for(int j = 0; j < bcols; j++) {
            float sum = 0;
            for(int k = 0; k < arows; k++) {
                sum += laMatGetRaw(A, i, k, acols) * laMatGetRaw(B, k, j, bcols);
            }
            laMatSetRaw(sum, C, j, i, ccols);
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

/*
 * Arbitrary Mat's
 */

Mat laMatNew(int rows, int cols) {
    Mat mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (float*)malloc(sizeof(float) * rows * cols);
    laMatFill(mat, 0.0f);
    return mat;
}

void laMatFree(Mat* mat) {
	mat->rows = 0;
	mat->cols = 0;
	free(mat->data);
	mat->data = NULL;
}

#endif
