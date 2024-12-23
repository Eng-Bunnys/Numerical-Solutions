#include "ApplicationHandler.h"
#include "Integrator/Simpson.h"
#include "Utils/InputHandler.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

static double function(double x)
{
    return 1.0 / (1.0 + x * x);
}

static double exactIntegral(double a, double b)
{
    return std::atan(b) - std::atan(a);
}

ApplicationHandler::ApplicationHandler() {}

void ApplicationHandler::run()
{
    printWelcomeMessage();
    handleSingleCalculation();
    std::cout << "\nThank you for using the integrator. Goodbye!\n";
}

void ApplicationHandler::printWelcomeMessage()
{
    std::cout << "=====================================================\n";
    std::cout << "Welcome! Compute definite integrals with custom bounds and accuracy.\n";
    std::cout << "=====================================================\n\n";
}

void ApplicationHandler::plot(const std::string &title, const std::string &function_name)
{
    std::ofstream configFile("plot_config.txt");
    if (configFile.is_open())
    {
        configFile << title << "\n";
        configFile << function_name << "\n";
        configFile.close();
        system("python plot_graph.py");
    }
    else
        std::cerr << "Error opening config file.\n";
}

void ApplicationHandler::handleSingleCalculation()
{
    InputHandler inputHandler;
    Simpson simpsonIntegrator;

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

    std::cout << "\nAnalyzing efficiency at different error tolerances...\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << std::setw(15) << "Tolerance" << std::setw(20) << "Subintervals Used"
              << std::setw(15) << "Integral" << std::setw(15) << "Error (%)" << "\n";
    std::cout << "-------------------------------------------------------\n";

    double tolerances[] = {1e-6, 1e-5, 1e-4, 1e-3, 1e-2};

    std::ofstream dataFile("plot_data.txt");
    if (dataFile.is_open())
    {
        for (double tolerance : tolerances)
        {
            double result = simpsonIntegrator.integrate(function, a, b, tolerance);
            int subintervalCount = simpsonIntegrator.getSubintervalCount();
            double exact = exactIntegral(a, b);
            double errorPercentage = (std::abs(exact - result) / std::abs(exact)) * 100;

            dataFile << tolerance << " " << subintervalCount << " " << result << " " << errorPercentage << "\n";

            std::cout << std::setw(15) << tolerance
                      << std::setw(20) << subintervalCount
                      << std::setw(15) << result
                      << std::setw(15) << errorPercentage << "%\n";
        }
        dataFile.close();
    }
    else
        std::cerr << "Error opening data file.\n";

    std::cout << "-------------------------------------------------------\n";

    std::cout << "\nEnter the desired accuracy (Press enter for default: 1e-6): ";
    std::string epsilonInput;
    std::cin.ignore();
    std::getline(std::cin, epsilonInput);
    epsilon = epsilonInput.empty() ? 1e-6 : std::stod(epsilonInput);

    double result = simpsonIntegrator.integrate(function, a, b, epsilon);
    int subintervalCount = simpsonIntegrator.getSubintervalCount();

    std::cout << "\n-------------------------------------------------------\n";
    std::cout << "Results for user-defined accuracy (" << epsilon << "):\n";
    std::cout << "-------------------------------------------------------\n";
    printResults(result, exactIntegral(a, b),
                 (std::abs(exactIntegral(a, b) - result) / std::abs(exactIntegral(a, b))) * 100,
                 a, b, epsilon, subintervalCount);

    std::string title = "Plot of Error vs Tolerance for Adaptive Simpson's Integration";
    std::string function_name = "f(x) = 1/(1+x^2)";
    plot(title, function_name);
}

void ApplicationHandler::printResults(double result, double exactValue, double errorPercentage, double a, double b, double epsilon, int subintervalCount)
{
    std::cout << "=====================================================\n";
    std::cout << std::setw(20) << std::left << "Parameter"
              << std::setw(20) << std::left << "Value"
              << "\n=====================================================\n";

    std::cout << std::setw(20) << "Lower Bound (a):" << std::setw(20) << a << "\n";
    std::cout << std::setw(20) << "Upper Bound (b):" << std::setw(20) << b << "\n";
    std::cout << std::setw(20) << "Desired Accuracy:" << std::setw(20) << epsilon << "\n";
    std::cout << std::setw(20) << "Subintervals Used:" << std::setw(20) << subintervalCount << "\n";
    std::cout << "=====================================================\n";

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "\n====================================\n";
    std::cout << std::setw(40) << "Result of the Adaptive Simpson's Integral:\n";
    std::cout << "====================================\n";
    std::cout << std::setw(20) << "Integral" << std::setw(10) << result << "\n";
    std::cout << std::setw(20) << "Exact Value" << std::setw(10) << exactValue << "\n";
    std::cout << std::setw(20) << "Error (%)" << std::setw(10) << errorPercentage << "%" << "\n";
    std::cout << "====================================\n";
}