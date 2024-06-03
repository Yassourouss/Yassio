#include <iostream>
#include <cmath>

void Pitch(double angle, double rotation[4][4]) {
    double cosA = cos(angle);
    double sinA = sin(angle);
    rotation[0][0] = 1; rotation[0][1] = 0; rotation[0][2] = 0; rotation[0][3] = 0;
    rotation[1][0] = 0; rotation[1][1] = cosA; rotation[1][2] = -sinA; rotation[1][3] = 0;
    rotation[2][0] = 0; rotation[2][1] = sinA; rotation[2][2] = cosA; rotation[2][3] = 0;
    rotation[3][0] = 0; rotation[3][1] = 0; rotation[3][2] = 0; rotation[3][3] = 1;
}

void Roll(double angle, double rotation[4][4]) {
    double cosA = cos(angle);
    double sinA = sin(angle);
    rotation[0][0] = cosA; rotation[0][1] = 0; rotation[0][2] = sinA; rotation[0][3] = 0;
    rotation[1][0] = 0; rotation[1][1] = 1; rotation[1][2] = 0; rotation[1][3] = 0;
    rotation[2][0] = -sinA; rotation[2][1] = 0; rotation[2][2] = cosA; rotation[2][3] = 0;
    rotation[3][0] = 0; rotation[3][1] = 0; rotation[3][2] = 0; rotation[3][3] = 1;
}

void Yaw(double angle, double rotation[4][4]) {
    double cosA = cos(angle);
    double sinA = sin(angle);
    rotation[0][0] = cosA; rotation[0][1] = -sinA; rotation[0][2] = 0; rotation[0][3] = 0;
    rotation[1][0] = sinA; rotation[1][1] = cosA; rotation[1][2] = 0; rotation[1][3] = 0;
    rotation[2][0] = 0; rotation[2][1] = 0; rotation[2][2] = 1; rotation[2][3] = 0;
    rotation[3][0] = 0; rotation[3][1] = 0; rotation[3][2] = 0; rotation[3][3] = 1;
}

void createTranslation(double tx, double ty, double tz, double translation[4][4]) {
    translation[0][0] = 1; translation[0][1] = 0; translation[0][2] = 0; translation[0][3] = tx;
    translation[1][0] = 0; translation[1][1] = 1; translation[1][2] = 0; translation[1][3] = ty;
    translation[2][0] = 0; translation[2][1] = 0; translation[2][2] = 1; translation[2][3] = tz;
    translation[3][0] = 0; translation[3][1] = 0; translation[3][2] = 0; translation[3][3] = 1;
}

void multiplyMatrices(const double mat1[4][4], const double mat2[4][4], double result[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void multiplyThreeMatrices(const double mat1[4][4], const double mat2[4][4], const double mat3[4][4], double result[4][4]) {
    double multipl1[4][4];
    multiplyMatrices(mat1, mat2, multipl1);
    multiplyMatrices(multipl1, mat3, result);
}

void printMatrix(const double matrix[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void multiplyMatrixVector(const double X[4][4], const double Y[4], double result[4]) {
    for (int i = 0; i < 4; ++i) {
        result[i] = 0;
        for (int j = 0; j < 4; ++j) {
            result[i] += X[i][j] * Y[j];
        }
    }
}
