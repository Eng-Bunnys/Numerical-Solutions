#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

double simpsonThreeEight(double columnValues[]) {
    double simpsonThreeOverEight = (3.0 / 8.0) * 0.2; 
    double Sum = columnValues[0] + columnValues[3] + 3 * (columnValues[1] + columnValues[2]); 
    return simpsonThreeOverEight * Sum; 
}

double newFormula(const std::vector<double>& fixedX) {
    double simpsonThreeOverEight = (3.0 / 8.0) * 0.1;
    double A = fixedX[0];
    double B = fixedX[1];
    double C = fixedX[2];
    double D = fixedX[3];
    double E = fixedX[4];

    return simpsonThreeOverEight * (A + E + 3 * (B + C) + 2 * D);
}

void printMatrix(double Matrix[5][6]) {
    std::cout << std::setw(8) << "x/y" << " | ";
    for (int col = 0; col < 6; col++) {
        std::cout << std::setw(8) << Matrix[0][col] << " ";
    }
    std::cout << "\n" << std::string(56, '-') << std::endl;

    for (int row = 1; row < 5; row++) {
        std::cout << std::setw(8) << Matrix[row][0] << " | ";
        for (int col = 1; col < 6; col++) {
            std::cout << std::setw(8) << Matrix[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void printColumnResults(double columnValues[], double x, double result) {
    std::cout << "\nAt x = " << x << ":\n" << std::string(10 + std::to_string(x).length(), '-') << std::endl;

    std::cout << std::setw(8) << "y" << " | ";
    double yValues[] = { 1.0, 1.3, 1.5, 1.7 };
    for (double y : yValues) {
        std::cout << std::setw(8) << y << " ";
    }
    std::cout << "\n" << std::string(8, '-') << "-+-" << std::string(8 * 4, '-') << std::endl;

    std::cout << std::setw(8) << "Value" << " | ";
    for (int i = 0; i < 4; i++) {
        std::cout << std::setw(8) << columnValues[i] << " ";
    }
    std::cout << "\n\nI = " << result << "\n\n";
}

int main() {
    double Matrix[5][6] = {
        {0.0, -0.2, -0.1, 0.0, 0.1, 0.2},
        {1.0, 4, 5, 2, 1, 7},          
        {1.3, 3, 2, 4, 8, 1},            
        {1.5, 6, 4, 5, 5, 3},             
        {1.7, 2, 7, 1, 9, 4}           
    };

    printMatrix(Matrix);

    std::vector<double> fixedX;

    for (int col = 1; col < 6; col++) {
        double columnValues[4];
        for (int row = 1; row < 5; row++) {
            columnValues[row - 1] = Matrix[row][col];
        }

        double result = simpsonThreeEight(columnValues);
        fixedX.push_back(result);

        printColumnResults(columnValues, Matrix[0][col], result);
    }

    std::cout << std::setw(8) << "x" << " | " << std::setw(8) << "I" << std::endl;
    std::cout << std::string(20, '-') << std::endl;
    for (int i = 0; i < fixedX.size(); i++) {
        std::cout << std::setw(8) << Matrix[0][i + 1] << " | " << std::setw(8) << fixedX[i] << std::endl;
    }

    double finalResult = newFormula(fixedX);
    std::cout << "\nValue of Integral: " << std::fixed << std::setprecision(4) << finalResult << std::endl;

    return 0;
}
