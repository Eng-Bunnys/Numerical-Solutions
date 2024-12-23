#ifndef Simpson_H
#define Simpson_H

class Simpson
{
private:
    // Represents a section (interval) of the area we want to calculate
    struct Interval
    {
        double a;       // Left endpoint (where the slice starts)
        double b;       // Right endpoint (where the slice ends) [a,b]
        double whole;   // Our current best guess at the area of this slice
        double epsilon; // How precise we want to be (smaller = more precise)

        Interval(double a_, double b_, double whole_, double epsilon_);
    };

    /**
     * Calculates Simpson's 3/8 rule for a single interval
     *
     * @param {function} The function to integrate
     * @param {number} The left endpoint
     * @param {number} The right endpoint
     * @returns {number} The approximate integral over [a,b]
     */
    double simpsonRule(double (*f)(double), double a, double b);

public:
    /**
     * Main integrator using adaptive quadrature
     *
     * @param {function} The function to integrate
     * @param {number} The lower bound of the integration
     * @param {number} The upper bound of the integration
     * @param {number} The desired precision (default: 1e-6)
     * @returns {number} The approximate definite integral of the function f from a to b
     */
    double integrate(double (*f)(double), double a, double b, double epsilon = 1e-6);

    // Function to get the number of subintervals
    int getSubintervalCount() const;

private:
    // Variable to keep track of the number of subintervals created
    mutable int subintervalCount = 0;
};

#endif // SIMPSON_H