#include "tbb/blocked_range.h"
#include "tbb/blocked_range2d.h"
#include "tbb/parallel_for.h"
#include "matrixParallelFor.h"

using namespace tbb;

struct ParallelMatrix2D {
	Matrix& A;
	Matrix& B;
	Matrix& C;
	int m;
	int r;

	ParallelMatrix2D(Matrix& _A, Matrix& _B, Matrix& _C) : 
		A(_A), B(_B), C(_C), m(B.getM()), r(A.getM())
	{}

	void operator() (const blocked_range2d<int>& range) const {
		for (int i = range.rows().begin(); i != range.rows().end(); ++i) {
			for (int k = 0; k < r; ++k) {
				for (int j = range.cols().begin(); j != range.cols().end(); ++j) {
					C(i, j) += A(i, k) * B(k, j);
				}
			}
		}
	}
};

struct ParallelMatrix1D {
	Matrix& A;
	Matrix& B;
	Matrix& C;
	int m;
	int r;

	ParallelMatrix1D(Matrix& _A, Matrix& _B, Matrix& _C) :
		A(_A), B(_B), C(_C), m(B.getM()), r(A.getM())
	{}

	void operator() (const blocked_range<int>& range) const {
		for (int i = range.begin(); i != range.end(); ++i) {
			for (int k = 0; k < r; ++k) {
				for (int j = 0; j < m; ++j) {
					C(i, j) += A(i, k) * B(k, j);
				}
			}
		}
	}
};

void matrix_multiplication_parallel_for_1D(Matrix& A, Matrix& B, Matrix& C)
{
	ParallelMatrix1D pm{ A, B, C };
	int n = A.getN();
	parallel_for(blocked_range<int>(0, n), pm);
}

void matrix_multiplication_parallel_for_2D(Matrix& A, Matrix& B, Matrix& C)
{
	ParallelMatrix2D pm{ A, B, C };
	int n = A.getN();
	int m = B.getM();
	parallel_for(blocked_range2d<int>(0, n, 0, m), pm);
}

