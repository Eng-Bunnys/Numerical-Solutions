#ifndef ApplicationHandler_H
#define ApplicationHandler_H

#include <string>

class ApplicationHandler {
public:
    ApplicationHandler();
    void run(); 
private:
    void printWelcomeMessage();
    void handleSingleCalculation();
    void printResults(double result, double exactValue, double errorPercentage, double a, double b, double epsilon, int subintervalCount);
};

#endif // ApplicationHandler_H