#pragma once
#include <iostream>

class Matrix {
private:
	int n;
	int m;
	int* data;
public:
	Matrix(int _n, int _m);
	Matrix(int _n, int _m, std::istream& is);
	~Matrix();

	int getN() { return n; }
	int getM() { return m; }

	int& operator()(int i, int j);
	const int& operator()(int i, int j) const;
	friend std::istream& operator>>(std::istream& is, Matrix& m);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
	bool operator==(Matrix& other);
};