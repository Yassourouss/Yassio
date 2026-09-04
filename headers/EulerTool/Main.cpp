#include <iostream>
#include <cmath>
#include "EulerRotationMatric.hpp"

int main() {

    std::cout << "Enter the object coordinates (x y z): ";
    double objectX, objectY, objectZ;
    std::cin >> objectX >> objectY >> objectZ;

    std::cout << "Enter Euler angles (in degrees) (angleX angleY angleZ): ";
    double angleX, angleY, angleZ;
    std::cin >> angleX >> angleY >> angleZ;
    angleX *= M_PI / 180.0;
    angleY *= M_PI / 180.0;
    angleZ *= M_PI / 180.0;

    std::cout << "Enter the order of transformation (e.g., XYZ, YZX, ...): ";
    std::string order;
    std::cin >> order;

    std::cout << "Enter the translation vector (tx ty tz): ";
    double tx, ty, tz;
    std::cin >> tx >> ty >> tz;

    double rotationX[4][4], rotationY[4][4], rotationZ[4][4];
    Pitch(angleX, rotationX);
    Roll(angleY, rotationY);
    Yaw(angleZ, rotationZ);

    double transformationMatrix[4][4];
    if (order == "XYZ") {
        multiplyThreeMatrices(rotationX, rotationY, rotationZ, transformationMatrix);
    }
    else if (order == "ZYX") {
        multiplyThreeMatrices(rotationZ, rotationY, rotationX, transformationMatrix);
    }
    else if (order == "YXZ") {
        multiplyThreeMatrices(rotationY, rotationX, rotationZ, transformationMatrix);
    }
    else if (order == "XZY") {
        multiplyThreeMatrices(rotationX, rotationZ, rotationY, transformationMatrix);
    }
    else if (order == "YZX") {
        multiplyThreeMatrices(rotationY, rotationZ, rotationX, transformationMatrix);
    }
    else if (order == "ZXY") {
        multiplyThreeMatrices(rotationZ, rotationX, rotationY, transformationMatrix);
    }
    else {
        std::cout << "Invalid transformation order.\n";
        return 1;
    }

    double translationMatrix[4][4];
    createTranslation(tx, ty, tz, translationMatrix);

    std::cout << "Rotation matrix around X axis:\n";
    printMatrix(rotationX);
    std::cout << "\nRotation matrix around Y axis:\n";
    printMatrix(rotationY);
    std::cout << "\nRotation matrix around Z axis:\n";
    printMatrix(rotationZ);

    std::cout << "\nTransformation matrix:\n";
    printMatrix(transformationMatrix);

    double objectPosition[4] = { objectX, objectY, objectZ, 1 };
    double transformedPosition[4];
    multiplyMatrixVector(transformationMatrix, objectPosition, transformedPosition);

    std::cout << "\nNew coordinate system after rotation:\n";
    std::cout << "x = " << transformedPosition[0] << ", y = " << transformedPosition[1] << ", z = " << transformedPosition[2] << "\n";

    transformedPosition[0] += tx;
    transformedPosition[1] += ty;
    transformedPosition[2] += tz;

    std::cout << "\nNew coordinate after translation and rotation:\n";
    std::cout << "x = " << transformedPosition[0] << ", y = " << transformedPosition[1] << ", z = " << transformedPosition[2] << "\n";

    return 0;
}

