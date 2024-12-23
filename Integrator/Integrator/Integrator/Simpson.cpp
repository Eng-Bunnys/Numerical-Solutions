#include "Simpson.h"
#include <cmath>
#include <iostream>
#include <vector>

Simpson::Interval::Interval(double a_, double b_, double whole_, double epsilon_)
    : a(a_), b(b_), whole(whole_), epsilon(epsilon_)
{
}

double Simpson::simpsonRule(double (*f)(double), double a, double b)
{
    double stepSize = (b - a) / 3.0;
    double x1 = a + stepSize;
    double x2 = a + 2 * stepSize;

    return (3.0 * stepSize / 8.0) * (f(a) + 3 * f(x1) + 3 * f(x2) + f(b));
}

double Simpson::integrate(double (*f)(double), double a, double b, double epsilon)
{
    struct Interval
    {
        double a, b, whole, epsilon;
    };

    std::vector<Interval> intervalStack;
    double result = 0.0;

    double initialWhole = simpsonRule(f, a, b);
    intervalStack.push_back({a, b, initialWhole, epsilon});

    subintervalCount = 1;

    while (!intervalStack.empty())
    {
        Interval current = intervalStack.back();
        intervalStack.pop_back();

        double midPoint = (current.a + current.b) / 2.0;
        double leftHalf = simpsonRule(f, current.a, midPoint);
        double rightHalf = simpsonRule(f, midPoint, current.b);

        double errorEstimate = fabs(leftHalf + rightHalf - current.whole);

        if (errorEstimate < 15 * current.epsilon)
        {
            result += leftHalf + rightHalf + errorEstimate / 15.0;
        }
        else
        {
            double halfEpsilon = current.epsilon / 2.0;
            intervalStack.push_back({midPoint, current.b, rightHalf, halfEpsilon});
            intervalStack.push_back({current.a, midPoint, leftHalf, halfEpsilon});

            subintervalCount += 2;
        }

        if (intervalStack.size() > 10000)
        {
            while (!intervalStack.empty())
            {
                const Interval &remaining = intervalStack.back();
                result += remaining.whole;
                intervalStack.pop_back();
            }
            break;
        }
    }

    return result;
}

int Simpson::getSubintervalCount() const
{
    return subintervalCount;
}
