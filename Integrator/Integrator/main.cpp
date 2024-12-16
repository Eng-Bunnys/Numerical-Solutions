#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <string>
#include <sstream>

#include "./Integrator/Simpson.h"
#include "InputParser.h"

double function(double x)
{
    return 1.0 / (1.0 + x * x);
}

int main()
{
    Simpson simpsonIntegrator;

    double a, b, epsilon;
    std::string input;

    std::cout << "=====================================================\n";
    std::cout << "Welcome! You will be asked to provide the bounds and desired accuracy.\n";
    std::cout << "=====================================================\n\n";

    std::cout << "Enter the lower bound (a) of the interval: ";
    while (true)
    {
        std::cin >> input;
        a = parsePiInput(input);
        if (a != -1)
            break;
        std::cout << "Invalid input. Please enter a valid number or 'pi' for Pi: ";
    }

    std::cout << "Enter the upper bound (b) of the interval: ";
    while (true)
    {
        std::cin >> input;
        b = parsePiInput(input);
        if (b != -1 && b > a)
            break;
        if (b <= a)
            std::cout << "Invalid input. The upper bound must be greater than the lower bound.\n";
        else
            std::cout << "Invalid input. Please enter a valid number or 'pi' for Pi: ";
    }

    std::cout << "Enter the desired accuracy (Press enter for default: 1e-6): ";
    std::string epsilonInput;
    std::getline(std::cin, epsilonInput);
    std::getline(std::cin, epsilonInput);
    if (epsilonInput.empty())
        epsilon = 1e-6;
    else
    {
        while (!(std::istringstream(epsilonInput) >> epsilon) || epsilon <= 0)
        {
            std::cout << "Invalid input. Please enter a positive number for epsilon: ";
            std::getline(std::cin, epsilonInput);
        }
    }

    system("CLS");

    std::cout << "=====================================================\n";
    std::cout << std::setw(20) << std::left << "Parameter"
              << std::setw(20) << std::left << "Value"
              << "\n=====================================================\n";

    std::cout << std::setw(20) << "Lower Bound (a):" << std::setw(20) << a << "\n";
    std::cout << std::setw(20) << "Upper Bound (b):" << std::setw(20) << b << "\n";
    std::cout << std::setw(20) << "Desired Accuracy:" << std::setw(20) << epsilon << "\n";
    std::cout << "=====================================================\n";

    double result = simpsonIntegrator.integrate(function, a, b, epsilon);

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "\n====================================\n";
    std::cout << std::setw(40) << "Result of the Adaptive Simpson's Integral:\n";
    std::cout << "====================================\n";
    std::cout << std::setw(20) << "Integral" << std::setw(10) << result << "\n";
    std::cout << "====================================\n";

    return 0;
}
