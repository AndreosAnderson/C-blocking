#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

void multiplyBlock(double** m1, double** m2, double** result, int N, int blockSize, int rowBlock, int colBlock, int kBlock);
void multiplyMatrix(double** m1, double** m2, double** result, int N, int blockSize);
double** allocateMatrix(int N);
void freeMatrix(double** matrix, int N);

#endif
