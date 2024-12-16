#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#ifndef PI
#define PI 3.14159265358979323846
#endif

#include <string>

// Define the function inline to prevent multiple definitions across translation units
inline double parsePiInput(const std::string &input)
{
    size_t piPos = input.find("pi");

    if (piPos != std::string::npos)
    {
        // Extract the portion before "pi" (if any) and the operator (*, /)
        std::string numberPart = input.substr(0, piPos);
        double number = 1.0; // Default multiplier is 1 if no number is provided

        if (!numberPart.empty())
        {
            // Try to convert the number part
            std::istringstream(numberPart) >> number;
        }

        // If there's any operator like '/' or '*' after "pi"
        std::string remainder = input.substr(piPos + 2); // Everything after "pi"

        if (!remainder.empty())
        {
            if (remainder == "/2")
                number = number / 2.0;
            else if (remainder == "*2")
                number = number * 2.0;
            else if (remainder == "*3")
                number = number * 3.0;
            else if (remainder.find("/") != std::string::npos)
            {
                // Handling division like "PI/2"
                size_t operatorPos = remainder.find("/");
                double divisor;
                std::istringstream(remainder.substr(operatorPos + 1)) >> divisor;
                number = number / divisor;
            }
            else if (remainder.find("*") != std::string::npos)
            {
                // Handle multiplication like "2*PI"
                size_t operatorPos = remainder.find("*");
                double multiplier;
                std::istringstream(remainder.substr(operatorPos + 1)) >> multiplier;
                number = number * multiplier;
            }
        }

        return number * PI; // Multiply the number by Pi
    }
    else
        return std::atof(input.c_str()); // Convert directly to double if no PI
}

#endif // INPUTPARSER_H
