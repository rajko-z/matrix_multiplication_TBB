#include <iostream>
#include <fstream>

#include "tbb/tick_count.h"
#include "Matrix.h"
#include "exceptions.h"
#include "matrixTaskGroup.h"
#include "utils.h";

using namespace std;
using namespace tbb;

int main()
{	
	Matrix* A = nullptr;
	Matrix* B = nullptr;
	Matrix* C = nullptr;

	tryToLoadMatrix(A, "../data/inA_1000x1000.txt", 1000, 1000);
	tryToLoadMatrix(B, "../data/inB_1000x1000.txt", 1000, 1000);
	exitProgramIfTwoMatricesCantBeMultiplied(*A, *B);
	C = new Matrix(A->getN(), B->getM());

	tick_count beg = tick_count::now();
	matrix_parallel_task_group(*A, *B, *C);
	tick_count end = tick_count::now();
	cout << "Time parallel: " << (end - beg).seconds() << '\n';

	ofstream rez("../data/resultTaskGroup.txt");
	rez << *C;


	return 0;
}