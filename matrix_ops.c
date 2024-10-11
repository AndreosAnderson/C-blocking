#include <stdlib.h>
#include <windows.h>
#include <psapi.h>
#include "matrix_ops.h"

void multiplyBlock(double** m1, double** m2, double** result, int N, int blockSize, int rowBlock, int colBlock, int kBlock) {
    for (int i = rowBlock; i < (rowBlock + blockSize) && i < N; i++) {
        for (int j = colBlock; j < (colBlock + blockSize) && j < N; j++) {
            double sum = 0;
            for (int k = kBlock; k < (kBlock + blockSize) && k < N; k++) {
                sum += m1[i][k] * m2[k][j];
            }
            result[i][j] += sum;
        }
    }
}

void multiplyMatrix(double** m1, double** m2, double** result, int N, int blockSize) {
    for (int i = 0; i < N; i += blockSize) {
        for (int j = 0; j < N; j += blockSize) {
            for (int k = 0; k < N; k += blockSize) {
                multiplyBlock(m1, m2, result, N, blockSize, i, j, k);
            }
        }
    }
}

double** allocateMatrix(int N) {
    double** matrix = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double*)malloc(N * sizeof(double));
    }
    return matrix;
}

void freeMatrix(double** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMemoryAndCPUUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    if (result) {
        printf("Memory usage: %ld KB\n", memCounter.WorkingSetSize / 1024);
    }

    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime)) {
        ULARGE_INTEGER kernel, user;
        kernel.LowPart = kernelTime.dwLowDateTime;
        kernel.HighPart = kernelTime.dwHighDateTime;
        user.LowPart = userTime.dwLowDateTime;
        user.HighPart = userTime.dwHighDateTime;

        double system_cpu_time = (double)kernel.QuadPart / 1e7;
        double user_cpu_time = (double)user.QuadPart / 1e7;

        printf("User CPU time: %f seconds\n", user_cpu_time);
        printf("System CPU time: %f seconds\n", system_cpu_time);
    }
}
