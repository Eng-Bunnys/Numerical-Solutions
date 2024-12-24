#ifndef Trapezoidal_H
#define Trapezoidal_H

#include <vector>

class Trapezoidal
{
private:
    int subintervalCount;

    struct Interval
    {
        double a, b, whole, epsilon;
        Interval(double a_, double b_, double whole_, double epsilon_);
    };

    double trapezoidalRule(double (*f)(double), double a, double b);

public:
    Trapezoidal();

    double integrate(double (*f)(double), double a, double b, double epsilon);

    int getSubintervalCount() const;
};

#endif // Trapezoidal_H
