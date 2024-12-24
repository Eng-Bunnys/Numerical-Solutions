#include "Trapezoidal.h"
#include <cmath>
#include <vector>
#include <iostream>

Trapezoidal::Interval::Interval(double a_, double b_, double whole_, double epsilon_)
    : a(a_), b(b_), whole(whole_), epsilon(epsilon_)
{
}

Trapezoidal::Trapezoidal() : subintervalCount(0) {}

double Trapezoidal::trapezoidalRule(double (*f)(double), double a, double b)
{
    return (b - a) / 2.0 * (f(a) + f(b));
}

double Trapezoidal::integrate(double (*f)(double), double a, double b, double epsilon)
{
    struct Interval
    {
        double a, b, whole, epsilon;
    };
    std::vector<Interval> intervalStack;
    double result = 0.0;
    double initialWhole = trapezoidalRule(f, a, b);
    intervalStack.push_back({a, b, initialWhole, epsilon});
    subintervalCount = 1;

    while (!intervalStack.empty())
    {
        if (intervalStack.size() > 10000)
            throw std::runtime_error("Failed to converge within iteration limit");

        Interval current = intervalStack.back();
        intervalStack.pop_back();

        double midPoint = (current.a + current.b) / 2.0;
        double leftHalf = trapezoidalRule(f, current.a, midPoint);
        double rightHalf = trapezoidalRule(f, midPoint, current.b);

        double errorEstimate = fabs(leftHalf + rightHalf - current.whole);

        if (errorEstimate < 3 * current.epsilon)
            result += leftHalf + rightHalf;
        else
        {
            double halfEpsilon = current.epsilon / 2.0;
            intervalStack.push_back({midPoint, current.b, rightHalf, halfEpsilon});
            intervalStack.push_back({current.a, midPoint, leftHalf, halfEpsilon});
            subintervalCount += 2;
        }
    }
    return result;
}

int Trapezoidal::getSubintervalCount() const
{
    return subintervalCount;
}