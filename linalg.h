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

#define MATGET(mat, row, col) (mat)->data[(col) * (mat)->cols + (row)]
#define MATGETBUF(data, row, col, cols) data[(col) * (cols) + (row)]
#define MATSET(x, mat, row, col) (mat)->data[(col) * (mat)->cols + (row)] = (x)

#define MAT4_ROWS 4
#define MAT4_COLS 4
#define VEC4_ROWS 4
#define VEC4_COLS 1

float randf(float vmin, float vmax) {
    return (float)rand()/(float)(RAND_MAX/(vmax - vmin))+vmin;
}

typedef struct {
    int rows;
    int cols;
    float* data;
} Mat; 

typedef struct {
	int rows;
	int cols;
	float data[16];
} Mat4;

#define NEW_MAT4 (Mat4){MAT4_ROWS, MAT4_COLS, {.0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f}}

typedef struct {
	int rows;
	int cols;
	float data[4];
} Vec4;

#define NEW_VEC4 (Vec4){VEC4_ROWS, VEC4_COLS, {.0f, .0f, .0f, .0f}}

void printmat(const float* data, int rows, int cols) {
    printf("[");
    for(int i = 0; i < rows; i++) {
        if(i > 0)
            printf(" ");
        for(int j = 0; j < cols; j++) {
            float v = MATGETBUF(data, i, j, cols);
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

#define PRINT_MAT(mat) printmat((mat)->data, (mat)->rows, (mat)->cols)

/*
 * Arbitrary Mat's
 */

void matfill(float val, Mat *A) {
    for(int i = 0; i < A->rows; i++) {
        for(int j = 0; j < A->cols; j++) {
            MATSET(val, A, i, j);
        }
    }
}

Mat mkmat(int rows, int cols) {
    Mat mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (float*)malloc(sizeof(float) * rows * cols);
    matfill(0, &mat);
    return mat;
}

void freemat(Mat* mat) {
	mat->rows = 0;
	mat->cols = 0;
	free(mat->data);
	mat->data = NULL;
}

void matadd(const Mat *A, const Mat *B, Mat *C) {
    if(A->rows != B->rows || A->cols != B->cols) {
        printf("[ERROR] Input matrix size does not match while trying to add!");
        return;
    }
    for(int i = 0; i < A->rows; i++) {
        for(int j = 0; j < A->cols; j++) {
        	MATSET(MATGET(A, i, j) + MATGET(B, i, j), C, i, j);
		}
    }
}

void matmul(const Mat *A, const Mat *B, Mat *C) {
    for(int i = 0; i < B->rows; i++) {
        for(int j = 0; j < B->cols; j++) {
            float sum = 0;
            for(int k = 0; k < A->rows; k++) {
                sum += MATGET(A, i, k) * MATGET(B, k, j);
            }
            MATSET(sum, C, j, i);
        }
    }
}

/*
 * Mat4's
 */

void mat4fill(float val, Mat4* A) {
    for(int i = 0; i < MAT4_ROWS; i++) {
        for(int j = 0; j < MAT4_COLS; j++) {
            MATSET(val, A, i, j);
        }
    }
}

void mat4add(const Mat4* A, const Mat4* B, Mat4* C) {
    for(int i = 0; i < MAT4_ROWS; i++) {
        for(int j = 0; j < MAT4_COLS; j++) {
        	MATSET(MATGET(A, i, j) + MATGET(B, i, j), C, i, j);
		}
    }
}

void mat4mul(const Mat4* A, const Mat4* B, Mat4* C) {
    for(int i = 0; i < MAT4_ROWS; i++) {
        for(int j = 0; j < MAT4_COLS; j++) {
            float sum = 0;
            for(int k = 0; k < MAT4_ROWS; k++) {
                sum += MATGET(A, i, k) * MATGET(B, k, j);
            }
            MATSET(sum, C, j, i);
        }
    }
}

void mat4vecmul(const Mat4* A, const Vec4* B, Vec4* C) {
    for(int i = 0; i < VEC4_ROWS; i++) {
        for(int j = 0; j < VEC4_COLS; j++) {
            float sum = 0;
            for(int k = 0; k < MAT4_ROWS; k++) {
                sum += MATGET(A, i, k) * MATGET(B, k, j);
            }
            MATSET(sum, C, j, i);
        }
    }
}

#endif
