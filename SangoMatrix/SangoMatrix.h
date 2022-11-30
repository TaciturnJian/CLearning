#pragma once

/*
	FileName : SangoMatrix
	Description : Simple matrix struct coded by sango, it's like object-based code in C anyway.
*/

#ifndef STDIO_H			//Used printf and scanf to display, input matrix
#define STDIO_H
#include <stdio.h>
#endif

#ifndef MALLOC_H		//Used malloc to create matrix
#define MALLOC_H
#include <malloc.h>
#endif

#ifndef SANGO_INCLUDE_SANGOMATRIX_H
#define SANGO_INCLUDE_SANGOMATRIX_H

#define MatAt(r,c) ->Box[r][c]

typedef unsigned int uint;
typedef double number;

/// <summary>
/// Simple matrix, include rows, cols, box. Remember to free your pointer.
/// </summary>
typedef struct {
	/// <summary>
	/// The row count of the matrix
	/// </summary>
	uint Rows;

	/// <summary>
	/// The column count of the matrix
	/// </summary>
	uint Cols;

	/// <summary>
	/// The numbers of the matrix
	/// </summary>
	number **Box;
} Matrix, Mat, *MatP;

/// <summary>
/// Create a matrix by input rows and cols
/// </summary>
/// <param name="rows">The row count of the matrix</param>
/// <param name="cols">The column count of the matrix</param>
/// <returns>the pointer to the matrix, 0 if error occurred</returns>
MatP CreateMatrix(uint rows, uint cols) {
	MatP matp = (MatP)malloc(sizeof(Mat));

	if (matp != 0) {
		matp->Rows = rows;
		matp->Cols = cols;
		matp->Box = (number **)malloc(rows * sizeof(number *));

		if (matp->Box == 0)		//just in case ... Visual Studio tells me not to do when matp->Box is nullptr
			return 0;

		for (int row = 0; row < rows; row++) {
			matp->Box[row] = (number *)malloc(cols * sizeof(number));	//ignore it, Visual Studio found an impossible error
		}

		return matp->Box == 0 ? 0 : matp;
	} 

	return 0;
}

/// <summary>
/// Ask user to input arguments of a matrix and create it
/// </summary>
/// <returns></returns>
MatP AskForMatrix() {
	printf("Input row count:");
	uint rows = 0;
	while (scanf("%d", &rows) == -1);			//actually, useless while?
	/*     ^^^ row ^^^     /     vvv column vvv     */
	printf("Input column count:");
	uint cols = 0;
	while (scanf("%d", &cols) == -1);

	return CreateMatrix(rows, cols);
}

/// <summary>
/// Ask user to input all numbers of a matrix
/// </summary>
/// <param name="matp"></param>
void FillMatrix(MatP matp) {
	printf("Tring to fill a matrix of size %d x %d \n", matp->Rows, matp->Cols);
	for (int r = 0; r < matp->Rows; r++) {
		for (int c = 0; c < matp->Cols; c++) {
			printf("(row:%d, col:%d) ", r + 1, c + 1);
			number n = 0;
			while (scanf("%lf", &n) == -1);
			matp MatAt(r, c) = n;
		}
	}
}

/// <summary>
/// print the matrix out
/// </summary>
/// <param name="matp"></param>
void PrintMatrix(MatP matp) {
	printf("Matrix Print Result£º[\n");
	for (int r = 0; r < matp->Rows; r++) {
		for (int c = 0; c < matp->Cols; c++) {
			printf("%lf ", matp MatAt(r, c));
		}
		printf("\n");
	}
	printf("]\n");
}

/// <summary>
/// Print numbers at X position
/// </summary>
/// <param name="matp"></param>
void PrintMatrixCross(MatP matp) {
	printf("Matrix Cross Print Result£º[\n");
	for (int r = 0; r < matp->Rows; r++) {
		for (int c = 0; c < matp->Cols; c++) {
			if ((r == c) || (r == matp->Rows - c - 1)) {
				printf("%lf ", matp MatAt(r, c));
			}
			else {
				printf("\t");
			}
		}
		printf("\n");
	}
	printf("]\n");
}

inline char SameSize(MatP a, MatP b) {
	return (a->Cols == b->Cols) && (a->Rows == b->Rows);
}

MatP SameSizeMatrixOperation(MatP a, MatP b, number (*opration)(number,number)) {
	if (opration == 0)
		return 0;

	if (SameSize(a, b)) {
		MatP result = CreateMatrix(a->Rows, a->Cols);
		for (int r = 0; r < result->Rows; r++) {
			for (int c = 0; c < result->Cols; c++) {
				result MatAt(r, c) = opration(a MatAt(r, c), b MatAt(r, c));
			}
		}
		return result;
	}
}

inline number MatrixOperation_NumberAdd(number a, number b) {
	return a + b;
}
inline number MatrixOperation_NumberSub(number a, number b) {
	return a - b;
}

inline MatP AddMatrix(MatP a, MatP b) {
	return SameSizeMatrixOperation(a, b, MatrixOperation_NumberAdd);
}

inline MatP SubMatrix(MatP a, MatP b) {
	return SameSizeMatrixOperation(a, b, MatrixOperation_NumberSub);
}

#endif