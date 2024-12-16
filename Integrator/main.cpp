#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>

#include "./Integrator/Simpson.h"
#include "InputParser.h"

static double function(double x)
{
    return 1.0 / (1.0 + x * x);
}

static double exactIntegral(double a, double b)
{
    return std::atan(b) - std::atan(a);
}

void generateCSV(const std::string& filename, double a_start, double a_end, double b_start, double b_end, double epsilon)
{
    std::ofstream file;
    file.open(filename, std::ios::out);

    if (!file)
    {
        std::cerr << "Error opening file for writing!\n";
        return;
    }

    file << "Lower Bound (a),Upper Bound (b),Error (%)\n";

    Simpson simpsonIntegrator;

    // Calculate dynamic step size based on the range
    double a_step = (a_end - a_start) / 50;  
    double b_step = (b_end - b_start) / 50;  

    // Loop over a range of values for a and b
    for (double a = a_start; a <= a_end; a += a_step)
    {
        for (double b = b_start; b <= b_end; b += b_step)
        {
            if (b <= a) continue;  // Ensure b > a

            double result = simpsonIntegrator.integrate(function, a, b, epsilon);

            double exactValue = exactIntegral(a, b);

            // Calculate the relative error in percentage
            double errorPercentage = (std::abs(exactValue - result) / std::abs(exactValue)) * 100;

            // Check if the error is infinity and skip this entry if true
            if (std::isinf(errorPercentage))
                continue;

            file << std::fixed << std::setprecision(15)
                << a << "," << b << "," << errorPercentage << "\n";
        }
    }

    file.close();
    std::cout << "CSV file generated successfully: " << filename << "\n";
}

int main()
{
    Simpson simpsonIntegrator;

    double a, b, epsilon;
    std::string input;
    std::string mode;

    std::cout << "=====================================================\n";
    std::cout << "Welcome! You will be asked to provide the bounds and desired accuracy.\n";
    std::cout << "=====================================================\n\n";

    std::cout << "Choose mode: \n1. Single Calculation\n2. Generate CSV for a range of a and b\nEnter choice: ";
    std::getline(std::cin, mode);

    // Single calculation mode
    if (mode == "1")
    {
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

        // Perform the integration using Simpson's rule
        double result = simpsonIntegrator.integrate(function, a, b, epsilon);

        // Calculate the exact value of the integral
        double exactValue = exactIntegral(a, b);

        // Calculate the relative error in percentage
        double errorPercentage = (std::abs(exactValue - result) / std::abs(exactValue)) * 100;

        std::cout << std::fixed << std::setprecision(15);
        std::cout << "\n====================================\n";
        std::cout << std::setw(40) << "Result of the Adaptive Simpson's Integral:\n";
        std::cout << "====================================\n";
        std::cout << std::setw(20) << "Integral" << std::setw(10) << result << "\n";
        std::cout << std::setw(20) << "Exact Value" << std::setw(10) << exactValue << "\n";
        std::cout << std::setw(20) << "Error (%)" << std::setw(10) << errorPercentage << "%" << "\n";
        std::cout << "====================================\n";
    }
    // CSV generation mode
    else if (mode == "2")
    {
        double a_start, a_end, b_start, b_end, epsilon = 1e-6;
        std::string input;

        std::cout << "Enter the starting value for a: ";
        while (true)
        {
            std::cin >> input;
            a_start = parsePiInput(input);
            if (a_start != -1)
                break;
            std::cout << "Invalid input. Please enter a valid number or 'pi' for Pi: ";
        }

        std::cout << "Enter the ending value for a: ";
        while (true)
        {
            std::cin >> input;
            a_end = parsePiInput(input);
            if (a_end != -1 && a_end > a_start)
                break;
            if (a_end <= a_start)
                std::cout << "Invalid input. The ending value for a must be greater than the starting value.\n";
            else
                std::cout << "Invalid input. Please enter a valid number or 'pi' for Pi: ";
        }

        std::cout << "Enter the starting value for b: ";
        while (true)
        {
            std::cin >> input;
            b_start = parsePiInput(input);
            if (b_start != -1 && b_start > a_start)
                break;
            if (b_start <= a_start)
                std::cout << "Invalid input. The starting value for b must be greater than the starting value for a.\n";
            else
                std::cout << "Invalid input. Please enter a valid number or 'pi' for Pi: ";
        }

        std::cout << "Enter the ending value for b: ";
        while (true)
        {
            std::cin >> input;
            b_end = parsePiInput(input);
            if (b_end != -1 && b_end > b_start)
                break;
            if (b_end <= b_start)
                std::cout << "Invalid input. The ending value for b must be greater than the starting value for b.\n";
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

        std::cin.ignore();  // Clear any remaining newline characters from the input buffer

        // Generate CSV
        generateCSV("integral_errors.csv", a_start, a_end, b_start, b_end, epsilon);
    }

    else
    {
        std::cout << "Invalid mode selected.\n";
    }

    return 0;
}
