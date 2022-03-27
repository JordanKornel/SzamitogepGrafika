#include "matrix.h"

void init_zero_matrix(float matrix[3][3]) {
    int i;
    int j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3]) {
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    printf("\n");
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]) {
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void init_identity_matrix(float matrix[3][3]) {
    int i;
    int j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                matrix[i][j] = 1.0;
            } else {
                matrix[i][j] = 0.0;
            }
        }
    }
}

void matrixScalarMultiplication(float matrix[3][3], float scalar) {
    int i;
    int j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matrix[i][j] *= scalar;
        }
    }
}

void multiply_matrices(float aMatrix[3][3], float bMatrix[3][3], float cMatrix[3][3]) {
    int i;
    int j;
    int k;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cMatrix[i][j] = 0.0f;
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                cMatrix[i][j] += aMatrix[i][k] * bMatrix[k][j];
            }
        }
    }
}

void pointTransformation(float matrix[3][3], float point[3], float returnVektor[3]) {
    int i, j, k;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            returnVektor[i] += matrix[i][j] * point[j];
        }
    }
}
void scale(float matrix[3][3], float s) {
    matrix[2][2] /= s;
}
void shift(float matrix[3][3], float vector[2]) {
    matrix[0][2] = vector[0];
    matrix[1][2] = vector[1];
}
void rotate(float matrix[3][3], float r) {
    float f = (r * PI) / 180;
    matrix[0][0] = cos(f);
    matrix[0][1] = -sin(f);
    matrix[1][0] = sin(f);
    matrix[1][1] = cos(f);
}