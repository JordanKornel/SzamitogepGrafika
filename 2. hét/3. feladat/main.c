#include "matrix.h"

int main(int argc, char** args) {
    float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];

	float aM[3][3];
	float bM[3][3] = {
        {1.8f, -4.0f, 9.5f},
        {7.65f, 6.45f, 4.56f},
        {-9.45f, 4.4f, -9.48f}
    };
    float cM[3][3];

    float m[3][3];
    float ve[3] = {9, 5, 1};
    float vr[3] = {0, 0, 0};
    float vs[2] = {5, 3};
    init_zero_matrix(m);
    m[2][2] = 1;
	
    init_identity_matrix(aM);
    print_matrix(aM);

    print_matrix(bM);
    matrixScalarMultiplication(bM, 9.8);
    print_matrix(bM);

    multiply_matrices(aM, bM, cM);
    print_matrix(cM);

    print_matrix(m);

    scale(m, 8);
    print_matrix(m);

    shift(m, vs);
    print_matrix(m);

    rotate(m, 90.0);
    print_matrix(m);

    pointTransformation(m, ve, vr);
    printf("%lf, %lf, %lf\n", vr[0], vr[1], vr[2]);
    return 0;
}