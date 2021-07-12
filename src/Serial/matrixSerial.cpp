#pragma once
#include "matrixSerial.h"

void matrix_multiplication_serial(Matrix& A, Matrix& B, Matrix& C)
{	
	int n = A.getN();
	int m = B.getM();
	int r = A.getM();

	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < r; ++k) {
			for (int j = 0; j < m; ++j) {
				C(i, j) += A(i, k) * B(k, j);
			}
		}
	}
}