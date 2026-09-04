#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

void Pitch(double angle, double rotation[4][4]);
void Roll(double angle, double rotation[4][4]);
void Yaw(double angle, double rotation[4][4]);
void createTranslation(double tx, double ty, double tz, double translation[4][4]);
void multiplyMatrices(const double mat1[4][4], const double mat2[4][4], double result[4][4]);
void multiplyThreeMatrices(const double mat1[4][4], const double mat2[4][4], const double mat3[4][4], double result[4][4]);
void printMatrix(const double matrix[4][4]);
void multiplyMatrixVector(const double X[4][4], const double Y[4], double result[4]);

#endif
