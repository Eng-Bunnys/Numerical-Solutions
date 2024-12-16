#include "Simpson.h"
#include <cmath>

Simpson::Interval::Interval(double a_, double b_, double whole_, double epsilon_)
    : a(a_), b(b_), whole(whole_), epsilon(epsilon_)
{
}

// Implementation of Simpson's 3/8 rule over a single interval
double Simpson::simpsonRule(double (*f)(double), double a, double b)
{
    // Divide the interval into three equal parts
    double stepSize = (b - a) / 3.0;

    /*
     Calculate the two internal points
     These are the points within the interval where we will evalute the fn.
    */
    double x1 = a + stepSize;
    double x2 = a + 2 * stepSize;

    // Apply Simpson's 3/8 formula:
    // (3h/8) * [f(a) + 3f(x1) + 3f(x2) + f(b)]
    return (3.0 * stepSize / 8.0) * (f(a) + 3 * f(x1) + 3 * f(x2) + f(b));
}

double Simpson::integrate(double (*f)(double), double a, double b, double epsilon)
{
    // Create a stack to store intervals we need to process
    std::vector<Interval> intervalStack;
    double result = 0.0;

    // Calculate the initial approx. for the whole interval
    double initialWhole = simpsonRule(f, a, b);

    // Early termination check: if the initial approximation is already accurate enough, return it, no need to waste resources
    if (fabs(initialWhole - simpsonRule(f, a, (a + b) / 2)) < 15 * epsilon)
        return initialWhole;

    // Add the initial interval to the stack
    intervalStack.emplace_back(a, b, initialWhole, epsilon);

    // Process intervals until the stack is empty
    while (!intervalStack.empty())
    {
        // Get the next interval to process
        Interval current = intervalStack.back();
        intervalStack.pop_back();

        // Calculate the midpoint and evaluate both halves
        double midPoint = (current.a + current.b) / 2.0;
        double leftHalf = simpsonRule(f, current.a, midPoint);
        double rightHalf = simpsonRule(f, midPoint, current.b);

        // Check if our approximation is accurate enough
        if (fabs(leftHalf + rightHalf - current.whole) < 15 * current.epsilon)
            // If so then we  add to result with Richardson extrapolation correction (ana mzkr 3la fekra :D)
            result += leftHalf + rightHalf +
                      (leftHalf + rightHalf - current.whole) / 15.0;
        else
        {
            // If not accurate enough, split the interval and continue processing
            // Add right half first (will be processed last)
            intervalStack.emplace_back(midPoint, current.b, rightHalf,
                                       current.epsilon / 2.0);
            // Add left half (will be processed first)
            intervalStack.emplace_back(current.a, midPoint, leftHalf,
                                       current.epsilon / 2.0);
        }

        // Safety check: if we have too many intervals (When testing the stack overflow error was not uncommon)
        if (intervalStack.size() > 10000)
        {
            // Emergency handling: add remaining approximations and exit to not lose any data
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