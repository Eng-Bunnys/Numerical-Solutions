#include "ApplicationHandler.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include "../Utils/InputHandler.h"
#include "../Integrator/Simpson.h"
#include "../Integrator/Trapezoidal.h"

static double function(double x)
{
    return 1.0 / (1.0 + x * x);
}

static double exactIntegral(double a, double b)
{
    return std::atan(b) - std::atan(a);
}

ApplicationHandler::ApplicationHandler()
{
    this->simpsonError = 0;
    this->trapezoidalError = 0;
    this->showGraph = true;
    this->deleteTextFiles = false;
    this->deleteGraphs = false;
    this->showExact = true;
    this->selectedMethod = IntegrationMethod::BOTH;
}

void ApplicationHandler::handleSingleCalculation()
{
    InputHandler inputHandler;
    Simpson simpsonIntegrator;
    Trapezoidal trapezoidalIntegrator;

    double a, b, epsilon;
    std::string input;

    std::cout << "Enter the lower bound (a) of the interval: ";
    while (true)
    {
        std::cin >> input;
        a = inputHandler.parsePiInput(input);
        if (!std::isnan(a))
            break;
        std::cout << "Invalid input. Please enter a valid number or 'pi' for Pi: ";
    }

    std::cout << "Enter the upper bound (b) of the interval: ";
    while (true)
    {
        std::cin >> input;
        b = inputHandler.parsePiInput(input);
        if (!std::isnan(b) && b > a)
            break;
        if (b <= a)
            std::cout << "Invalid input. The upper bound must be greater than the lower bound.\n";
        else
            std::cout << "Invalid input. Please enter a valid number or 'pi' for Pi: ";
    }

    std::cout << "\nComparing methods at different error tolerances...\n";
    double tolerances[] = {1e-6, 1e-5, 1e-4, 1e-3, 1e-2};
    int numTolerances = sizeof(tolerances) / sizeof(tolerances[0]);

    printComparisonTable(a, b, tolerances, numTolerances);

    std::cout << "\nEnter the desired accuracy (Press enter for default: 1e-6): ";
    std::string epsilonInput;
    std::cin.ignore();
    std::getline(std::cin, epsilonInput);
    epsilon = epsilonInput.empty() ? 1e-6 : std::stod(epsilonInput);

    double exactValue = exactIntegral(a, b);
    double simpsonResult, trapResult;
    std::chrono::duration<double, std::milli> simpsonTime, trapTime;
    int simpsonSubintervalCount = 0;
    int trapSubintervalCount = 0;

    if (selectedMethod == IntegrationMethod::SIMPSON ||
        selectedMethod == IntegrationMethod::BOTH)
    {
        auto start = std::chrono::high_resolution_clock::now();
        simpsonResult = simpsonIntegrator.integrate(function, a, b, epsilon);
        auto end = std::chrono::high_resolution_clock::now();
        simpsonTime = end - start;

        this->simpsonError = (std::abs(exactValue - simpsonResult) / std::abs(exactValue)) * 100;
        simpsonSubintervalCount = simpsonIntegrator.getSubintervalCount();
    }

    if (selectedMethod == IntegrationMethod::TRAPEZOIDAL ||
        selectedMethod == IntegrationMethod::BOTH)
    {
        auto start = std::chrono::high_resolution_clock::now();
        trapResult = trapezoidalIntegrator.integrate(function, a, b, epsilon);
        auto end = std::chrono::high_resolution_clock::now();
        trapTime = end - start;

        this->trapezoidalError = (std::abs(exactValue - trapResult) / std::abs(exactValue)) * 100;
        trapSubintervalCount = trapezoidalIntegrator.getSubintervalCount();
    }

    std::cout << "\n=============== Final Results ===============\n\n";

    if (selectedMethod == IntegrationMethod::SIMPSON ||
        selectedMethod == IntegrationMethod::BOTH)
    {
        printResults("Simpson's Method", simpsonResult, exactValue,
                     this->simpsonError, a, b, epsilon,
                     simpsonSubintervalCount,
                     simpsonTime.count());
    }

    if (selectedMethod == IntegrationMethod::TRAPEZOIDAL ||
        selectedMethod == IntegrationMethod::BOTH)
    {
        printResults("Trapezoidal Method", trapResult, exactValue,
                     this->trapezoidalError, a, b, epsilon,
                     trapSubintervalCount,
                     trapTime.count());
    }

    if (this->showGraph)
        displayGraphs();
}

void ApplicationHandler::printComparisonTable(double a, double b,
                                              const double *tolerances,
                                              int numTolerances)
{
    Simpson simpsonIntegrator;
    Trapezoidal trapezoidalIntegrator;

    double simpsonResults[5], trapResults[5];
    double simpsonErrors[5], trapErrors[5];
    int simpsonSubintervals[5], trapSubintervals[5];

    if (selectedMethod == IntegrationMethod::SIMPSON ||
        selectedMethod == IntegrationMethod::BOTH)
    {
        std::cout << "\nSimpson's Method Results:\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << std::setw(15) << "Tolerance" << std::setw(20) << "Subintervals Used"
                  << std::setw(15) << "Integral" << std::setw(15) << "Error (%)" << "\n";
        std::cout << "-------------------------------------------------------\n";

        for (int i = 0; i < numTolerances; i++)
        {
            double result = simpsonIntegrator.integrate(function, a, b, tolerances[i]);
            int subintervalCount = simpsonIntegrator.getSubintervalCount();
            double exact = exactIntegral(a, b);
            double errorPercentage = (std::abs(exact - result) / std::abs(exact)) * 100;

            simpsonResults[i] = result;
            simpsonErrors[i] = errorPercentage;
            simpsonSubintervals[i] = subintervalCount;

            std::cout << std::setw(15) << tolerances[i]
                      << std::setw(20) << subintervalCount
                      << std::setw(15) << result
                      << std::setw(15) << errorPercentage << "%\n";
        }

        generateDataFile("plot_data_simpson.txt", tolerances, simpsonResults,
                         simpsonErrors, simpsonSubintervals, numTolerances);
    }

    if (selectedMethod == IntegrationMethod::TRAPEZOIDAL ||
        selectedMethod == IntegrationMethod::BOTH)
    {
        std::cout << "\nTrapezoidal Method Results:\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << std::setw(15) << "Tolerance" << std::setw(20) << "Subintervals Used"
                  << std::setw(15) << "Integral" << std::setw(15) << "Error (%)" << "\n";
        std::cout << "-------------------------------------------------------\n";

        for (int i = 0; i < numTolerances; i++)
        {
            double result = trapezoidalIntegrator.integrate(function, a, b, tolerances[i]);
            int subintervalCount = trapezoidalIntegrator.getSubintervalCount();
            double exact = exactIntegral(a, b);
            double errorPercentage = (std::abs(exact - result) / std::abs(exact)) * 100;

            trapResults[i] = result;
            trapErrors[i] = errorPercentage;
            trapSubintervals[i] = subintervalCount;

            std::cout << std::setw(15) << tolerances[i]
                      << std::setw(20) << subintervalCount
                      << std::setw(15) << result
                      << std::setw(15) << errorPercentage << "%\n";
        }

        generateDataFile("plot_data_trap.txt", tolerances, trapResults,
                         trapErrors, trapSubintervals, numTolerances);
    }
}

void ApplicationHandler::printResults(const std::string &method, double result,
                                      double exactValue, double errorPercentage,
                                      double a, double b, double epsilon,
                                      int subintervalCount, double computeTime)
{
    std::cout << "Results for " << method << ":\n";
    std::cout << "=====================================================\n";
    std::cout << std::setw(20) << std::left << "Parameter"
              << std::setw(20) << std::left << "Value"
              << "\n=====================================================\n";

    std::cout << std::setw(20) << "Lower Bound (a):" << std::setw(20) << a << "\n";
    std::cout << std::setw(20) << "Upper Bound (b):" << std::setw(20) << b << "\n";
    std::cout << std::setw(20) << "Desired Accuracy:" << std::setw(20) << epsilon << "\n";
    std::cout << std::setw(20) << "Subintervals Used:" << std::setw(20) << subintervalCount << "\n";
    std::cout << std::setw(20) << "Compute Time:" << std::setw(20) << computeTime << " ms\n";
    std::cout << "=====================================================\n";

    std::cout << std::fixed << std::setprecision(15);
    std::cout << std::setw(20) << "Integral" << std::setw(10) << result << "\n";
    if (showExact)
    {
        std::cout << std::setw(20) << "Exact Value" << std::setw(10) << exactValue << "\n";
        std::cout << std::setw(20) << "Error (%)" << std::setw(10) << errorPercentage << "%" << "\n";
    }
    std::cout << "=====================================================\n\n";
}