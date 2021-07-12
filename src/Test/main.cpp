#include <iostream>
#include <fstream>

#include "Matrix.h"
#include "exceptions.h"
#include "utils.h";

using namespace std;

int main()
{	
	Matrix* A = nullptr;
	Matrix* B = nullptr;
	Matrix* C = nullptr;

	int n = 2048;
	int m = 2048;

	// prvo pokrenuti svaku verziju algoritma sa istim ulazima da bi rezultujuci fajl bio azuriran
	// ako je sve ispravno, sva tri fajla ce sadrzati istu matricu
	tryToLoadMatrix(A, "../data/resultSerial.txt", n, m);
	tryToLoadMatrix(B, "../data/resultParallelFor.txt", n, m);
	tryToLoadMatrix(C, "../data/resultTaskGroup.txt", n, m);

	if (*A == *B && *A == *C)
		cout << "SUCCESS";
	else
		cout << "FAILURE";

	return 0;
}