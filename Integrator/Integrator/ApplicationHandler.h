#ifndef ApplicationHandler_H
#define ApplicationHandler_H

#include <string>

class ApplicationHandler
{
public:
    ApplicationHandler();
    void run();
    double simpsonError;
    double trapezoidalError;

private:
    void printWelcomeMessage();
    void handleSingleCalculation();

    void printResults(const std::string &method, double result, double exactValue,
                      double errorPercentage, double a, double b,
                      double epsilon, int subintervalCount);
    void printComparisonTable(double a, double b, const double *tolerances,
                              int numTolerances);

    void plot(const std::string &title, const std::string &function_name,
              const std::string &filename_suffix);

    void generateDataFile(const std::string &filename,
                          const double *tolerances, const double *results,
                          const double *errors, const int *subintervals,
                          int numTolerances);

    void displayGraphs();
};

#endif // ApplicationHandler_H