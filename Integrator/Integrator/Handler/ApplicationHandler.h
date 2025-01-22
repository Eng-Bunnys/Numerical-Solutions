#ifndef ApplicationHandler_H
#define ApplicationHandler_H
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include "../Utils/InputHandler.h"
#include "../Integrator/Simpson.h"
#include "../Integrator/Trapezoidal.h"

enum class IntegrationMethod
{
    SIMPSON,
    TRAPEZOIDAL,
    BOTH
};

enum class Mode
{
    Result = 0x3,
    Compare = 0x4
};

class ApplicationHandler
{
public:
    ApplicationHandler();
    void run();
    double simpsonError;
    double trapezoidalError;
    bool showGraph;
    void setShowGraph(bool x);
    void setDeleteTextFiles(bool x);
    void setDeleteGraphs(bool x);
    void setMethod(IntegrationMethod method);

    std::string getMethod() const;

private:
    bool deleteTextFiles;
    bool deleteGraphs;
    IntegrationMethod selectedMethod;
    std::vector<std::string> generatedFiles;

    void printWelcomeMessage();
    void handleSingleCalculation();
    void askSettings();
    void printResults(const std::string &method, double result, double exactValue,
                      double errorPercentage, double a, double b,
                      double epsilon, int subintervalCount);
    void printComparisonTable(double a, double b, const double *tolerances,
                              int numTolerances);
    void printSettings();
    void plot(const std::string &title, const std::string &function_name,
              const std::string &filename_suffix);
    void generateDataFile(const std::string &filename,
                          const double *tolerances, const double *results,
                          const double *errors, const int *subintervals,
                          int numTolerances);
    void displayGraphs();
    void cleanUpFiles();
    void trackFile(const std::string &filename);
    void selectIntegrationMethod();
};
#endif // ApplicationHandler_H