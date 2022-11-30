#define _CRT_SECURE_NO_WARNINGS 1

#include "SangoMatrix.hpp"

int main() {
	MatP matp = AskForMatrix();
	FillMatrix(matp);
	PrintMatrix(matp);
	PrintMatrixCross(matp);
}
