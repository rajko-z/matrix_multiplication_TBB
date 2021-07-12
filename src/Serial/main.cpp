#include <iostream>
#include <fstream>

#include "tbb/tick_count.h"
#include "Matrix.h"
#include "matrixSerial.h"
#include "exceptions.h"
#include "utils.h";

using namespace std;
using namespace tbb;

int main()
{	
	Matrix* A = nullptr;
	Matrix* B = nullptr;
	Matrix* C = nullptr;

	tryToLoadMatrix(A, "../data/inA_500x500.txt", 500, 500);
	tryToLoadMatrix(B, "../data/inB_500x500.txt", 500, 500);
	exitProgramIfTwoMatricesCantBeMultiplied(*A, *B);

	C = new Matrix(A->getN(), B->getM());

	tick_count beg = tick_count::now();
	matrix_multiplication_serial(*A, *B, *C);
	tick_count end = tick_count::now();
	cout << "Time serial: " << (end - beg).seconds() << '\n';

	ofstream rez("../data/resultSerial.txt");
	rez << *C;


	return 0;
}