#pragma once
#include "Matrix.h";
void tryToLoadMatrix(Matrix*& matrix, const char* fileName, int n, int m);
void exitProgramIfTwoMatricesCantBeMultiplied(Matrix& A, Matrix& B);