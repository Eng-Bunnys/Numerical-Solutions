#include "Trapezoidal.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

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
    intervalStack.push_back({ a, b, initialWhole, epsilon });
    subintervalCount = 1;

    std::ofstream intervalFile("intervals_log.txt");
    if (!intervalFile)
        throw std::runtime_error("Unable to open file for logging intervals");
    intervalFile << "Intervals processed during integration:\n";
    intervalFile << "a\tb\twhole\tepsilon\n";

    while (!intervalStack.empty())
    {
        Interval current = intervalStack.back();
        intervalStack.pop_back();

        double midPoint = (current.a + current.b) / 2.0;
        double leftHalf = trapezoidalRule(f, current.a, midPoint);
        double rightHalf = trapezoidalRule(f, midPoint, current.b);
        double errorEstimate = fabs(leftHalf + rightHalf - current.whole);

        if (errorEstimate < 15 * current.epsilon)
        {
            result += leftHalf + rightHalf;
            intervalFile << current.a << "\t" << current.b << "\t"
                << current.whole << "\t" << current.epsilon << "\n";
        }
        else
        {
            double halfEpsilon = current.epsilon / 2.0;
            intervalStack.push_back({ midPoint, current.b, rightHalf, halfEpsilon });
            intervalStack.push_back({ current.a, midPoint, leftHalf, halfEpsilon });
            subintervalCount += 2;
        }

        if (intervalStack.size() > 10000)
        {
            while (!intervalStack.empty())
            {
                const Interval& remaining = intervalStack.back();
                result += remaining.whole;
                intervalStack.pop_back();
            }
            break;
        }
    }

    intervalFile.close();
    return result;
}

int Trapezoidal::getSubintervalCount() const
{
    return subintervalCount;
}
