#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <vector>

// Function used to compute the factorial of a number since one doesn't natively exist
unsigned long long factorial(int number)
{
    if (number < 0)
        throw std::invalid_argument("You cannot get the factorial for negative numbers.");

    unsigned long long result = 1;

    for (int i = 2; i <= number; ++i)
        result *= i;

    return result;
}

// Simple fn to compute the value of y at any point
double computeRealY(double x)
{
    return pow(x, 3) - tanh(x);
}

// Simple fn to calc the vlaue of alpha
double computeAlpha(double x, double xo, double h)
{
    return (x - xo) / h;
}

// Getting the difference table, differences[col no., row no.]
std::vector<std::vector<double>> computeDifferenceTable(double xStart, double xEnd, double h)
{
    int numberOfPoints = static_cast<int>((xEnd - xStart) / h) + 1;
    std::vector<double> yValues(numberOfPoints);
    std::vector<std::vector<double>> differences(6); // 6 bec. y, delta y, delta^2 y, ..., delta^5 y

    // Calcing the y values for each x then storing them in the first row
    for (int i = 0; i < numberOfPoints; ++i)
    {
        double x = xStart + i * h;
        yValues[i] = computeRealY(x);
        differences[0].push_back(yValues[i]); // Storing all y values
    }

    // Cacling the differences for all orders 1 to 5
    for (int order = 1; order <= 5; ++order)
    {
        // 2nd loop to iterate through the prev order's differences to calc the next order
        for (int i = 0; i < differences[order - 1].size() - 1; ++i)
        {
            // Calcing the diff. between consecutive values
            double diff = differences[order - 1][i + 1] - differences[order - 1][i];
            differences[order].push_back(diff);
        }
    }

    return differences;
}

// Fn. to calc the derivative of the Taylor Series until the 5th element
/* Formula: Δy +
 (Δ^2y / 2!) (2α -1)
 + (Δ^3y / 3!)(3α^2 - 6α + 2)
 + (Δ^4y/4!)(4α^3 - 18α^2 + 22α -6)
 + (Δ^5y/5!)(5α^4-40α^3+105α^2-100α+24) */
double computeDerivative(const std::vector<std::vector<double>> &differences, double alpha)
{
    double derivative = differences[1][0] + (differences[2][0] / factorial(2)) * ((2 * alpha - 1)) + (differences[3][0] / factorial(3)) * ((3 * pow(alpha, 2)) - (6 * alpha) + 2) + (differences[4][0] / factorial(4)) * ((4 * pow(alpha, 3)) - (18 * pow(alpha, 2)) + (22 * alpha) - 6) + (differences[5][0] / factorial(5)) * ((5 * pow(alpha, 4)) - (40 * pow(alpha, 3) + (105 * pow(alpha, 2) - (100 * alpha) + 24)));
    return derivative;
}

// Getting the exact value
double computeExactDerivative(double x)
{
    return 3 * pow(x, 2) - pow(1 / cosh(x), 2);
}

int main()
{
    double xStart = 0.0;
    double xEnd = 0.5;
    double stepSize = 0.1;

    // Getting the difference table
    std::vector<std::vector<double>> differences = computeDifferenceTable(xStart, xEnd, stepSize);

    // Display the header , setw() -> set width, used to specify the min no. of characters to be written in the next output
    std::cout << std::setw(10) << "x"
              << std::setw(15) << "y"
              << std::setw(15) << "delta y"
              << std::setw(15) << "delta^2 y"
              << std::setw(15) << "delta^3 y"
              << std::setw(15) << "delta^4 y"
              << std::setw(15) << "delta^5 y" << std::endl;

    std::cout << std::string(105, '-') << std::endl;

    // Display the computed values
    for (size_t i = 0; i < differences[0].size(); ++i)
    {
        std::cout << std::fixed << std::setprecision(4)
                  << std::setw(10) << (xStart + i * stepSize)
                  << std::setw(15) << differences[0][i];

        for (size_t order = 1; order < differences.size(); ++order)
        {
            if (i < differences[order].size())
            {
                std::cout << std::setw(15) << std::setprecision(4) << differences[order][i];
            }
            else
            {
                std::cout << std::setw(15) << "-"; // if there's no value
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    double alpha = computeAlpha(0.3, xStart, stepSize);
    double derivative = computeDerivative(differences, alpha);

    double ydash = derivative / stepSize;

    double exactValue = computeExactDerivative(0.3);

    double percentageError = (fabs(exactValue - ydash) / fabs(exactValue)) * 100;

    // Display the second table header
    std::cout << std::string(80, '-') << std::endl;
    std::cout << std::setw(30) << "Computed Values"
              << std::setw(30) << "Exact Value & Error" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    // Display computed derivative and exact value
    std::cout << std::setw(30) << "Computed dy/dx: " << std::fixed << std::setprecision(4) << ydash << std::endl;
    std::cout << std::setw(30) << "Exact dy/dx at x = 0.3: " << std::fixed << std::setprecision(4) << exactValue << std::endl;
    std::cout << std::setw(30) << "Percentage Error: " << std::fixed << std::setprecision(4) << percentageError << "%" << std::endl;

    return 0;
}
