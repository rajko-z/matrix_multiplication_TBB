#include "utils.h"
#include "exceptions.h"
#include "fstream";
using namespace std;

void tryToLoadMatrix(Matrix*& matrix, const char* fileName, int n, int m) 
{
	try {
		ifstream ina(fileName);
		matrix = new Matrix(n, m, ina);
	}
	catch (InvalidDimensions& e) {
		cout << e.massage;
		exit(-1);
	}
	catch (BadFileFormat& e) {
		cout << e.massage;
		exit(-1);
	}
	catch (InvalidStream e) {
		cout << e.massage;
		exit(-1);
	}
	catch (...) {
		cout << "Error happend while trying to load Matrix from file";
		exit(-1);
	}
}

void exitProgramIfTwoMatricesCantBeMultiplied(Matrix& A, Matrix& B)
{
	if (A.getM() != B.getN()) {
		cout << "Loaded matrices can't be multiplied. Dimensions A(" << A.getN() << ',' << A.getM()
			<< ")  B(" << B.getN() << "," << B.getM() << ")\n";
		exit(-1);
	}
}

