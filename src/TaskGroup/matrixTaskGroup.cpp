#include "matrixTaskGroup.h"
#include "tbb/task_group.h"
#define NUMBER_OF_PHYSICAL_CORES 2
#define NUMBER_OF_LOGICAL_CORES 4

using namespace std;
using namespace tbb;


void _parallel_task_for_each_row(Matrix& A, Matrix& B, Matrix& C, int n, int low, int high)
{
	if (low == high)
	{
		int m = B.getM();
		int r = A.getM();
		
		for (int i = low; i <= high; ++i) {
			for (int k = 0; k < r; ++k) {
				for (int j = 0; j < m; ++j) {
					C(i, j) += A(i, k) * B(k, j);
				}
			}
		}
		return;
	}
	int mid = (low + high) / 2;
	task_group g;
	g.run([&] {_parallel_task_for_each_row(A, B, C, n, low, mid); });
	g.run([&] {_parallel_task_for_each_row(A, B, C, n, mid + 1, high); });
	g.wait();
}


void _parallel_task_relative_to_number_of_cores(Matrix& A, Matrix& B, Matrix& C, int n, int low, int high, int cores)
{	
	// ovde se pod poslom misli na broj redova koje ce jedan task da izracuna
	// matrica ima n redova
	// najbolja podela ako je broj redova deljiv sa brojem jezgara

	int curr_work = high - low + 1; // indeksi idu od 0 od n-1 (npr 0..1 su 2 dva reda)
	int work_per_core = n / cores;

	if (curr_work <= work_per_core)
	{
		int m = B.getM();
		int r = A.getM();

		for (int i = low; i <= high; ++i) {
			for (int k = 0; k < r; ++k) {
				for (int j = 0; j < m; ++j) {
					C(i, j) += A(i, k) * B(k, j);
				}
			}
		}
		return;
	}
	int mid = (low + high) / 2;
	task_group g;
	g.run([&] {_parallel_task_relative_to_number_of_cores(A, B, C, n, low, mid, 2); });
	g.run([&] {_parallel_task_relative_to_number_of_cores(A, B, C, n, mid + 1, high, 2); });
	g.wait();
}


void _parallel_task_even_split(Matrix& A, Matrix& B, Matrix& C, int ai, int aj, int bi, int bj)
{
	int N = A.getN();
	int M = B.getM();

	if ((bi - ai) <= N / 2 && (bj - aj) <= M / 2)
	{	
		int m = B.getM();
		int r = A.getM();

		for (int i = ai; i <= bi; ++i) {
			for (int k = 0; k < r; ++k) {
				for (int j = aj; j <= bj; ++j) {
					C(i, j) += A(i, k) * B(k, j);
				}
			}
		}
		return;
	}
	task_group g;
	int midi = (ai + bi) / 2;
	int midj = (aj + bj) / 2;
	g.run([&] {_parallel_task_even_split(A, B, C, ai, aj, midi, midj); });
	g.run([&] {_parallel_task_even_split(A, B, C, ai, midj + 1, midi, bj); });
	g.run([&] {_parallel_task_even_split(A, B, C, midi + 1, aj, bi, midj); });
	g.run([&] {_parallel_task_even_split(A, B, C, midi + 1, midj + 1, bi, bj); });
	g.wait();
}



void matrix_parallel_task_group(Matrix& A, Matrix& B, Matrix& C) 
{
	int n = A.getN();
	int m = B.getM();
	//_parallel_task_for_each_row(A, B, C, n, 0, n-1);

	//_parallel_task_relative_to_number_of_cores(A, B, C, n, 0, n - 1, NUMBER_OF_PHYSICAL_CORES);
	_parallel_task_even_split(A, B, C, 0, 0, n - 1, m - 1);

}
