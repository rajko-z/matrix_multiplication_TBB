#include "Matrix.h"
#include "exceptions.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

Matrix::Matrix(int _n, int _m) : n(_n), m(_m), data(nullptr)
{
	data = (int*)calloc(n * m, sizeof(int));
}

Matrix::Matrix(int _n, int _m, std::istream& is) : n(_n), m(_m), data(nullptr)
{
	data = (int*)calloc(n * m, sizeof(int));
	is >> *this;
}

Matrix::~Matrix()
{
	delete[] data;
}

bool Matrix::operator==(Matrix& other) {
	if (n != other.getN() || m != other.getM())
		return false;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (data[i * m + j] != other(i, j))
				return false;
		}
	}
	return true;
}

int& Matrix::operator()(int i, int j) {
	return data[i * m + j];
}

const int& Matrix::operator()(int i, int j) const {
	return data[i * m + j];
}

std::istream& operator>>(std::istream& is, Matrix& matrix)
{	
	if (!is)
		throw InvalidStream("Trying to read from invalid stream");

	int a, b;
	is >> a >> b;
	if (a != matrix.getN() || b != matrix.getM()) {
		ostringstream ss;
		ss << "Dimensions of stream and matrix are incompatible:" << endl
			<< "Stream dimensions (" << a << "," << b << ")" << endl
			<< "Matrix dimensions (" << matrix.getN() << "," << matrix.getM() << ")";
		throw InvalidDimensions(ss.str());
	}

	int br = 0;
	while (is >> matrix.data[br]) {
		++br;
	}
	if (is.eof()) {
		return is;
	}
	else {
		throw BadFileFormat("Error happend while trying to read data from file to matrix");
	}
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{	
	os << matrix.n << " " << matrix.m << '\n';
	for (int i = 0; i < matrix.n; ++i) {
		for (int j = 0; j < matrix.m; ++j) {
			os << matrix(i, j) << " ";
		}
		os << '\n';
	}
	return os;
}
