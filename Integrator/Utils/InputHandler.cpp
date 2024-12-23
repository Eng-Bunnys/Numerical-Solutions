#include "InputHandler.h"
#include <regex>
#include <sstream>

std::string InputHandler::trimWhitespace(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

double InputHandler::parsePiInput(const std::string& input)
{
    std::string trimmedInput = trimWhitespace(input);
    if (trimmedInput.empty())
        return NAN;

    bool isNegative = false;
    if (trimmedInput[0] == '-')
    {
        isNegative = true;
        trimmedInput = trimmedInput.substr(1);
    }

    std::regex pattern(R"(([-+]?[0-9]*\.?[0-9]*)\s*\*?\s*pi\s*(?:([*/])\s*([-+]?[0-9]*\.?[0-9]*))?)");
    std::smatch match;

    if (std::regex_match(trimmedInput, match, pattern))
    {
        double multiplier = 1.0;
        double divisor = 1.0;

        if (!match[1].str().empty())
            multiplier = std::stod(match[1].str());

        if (!match[2].str().empty() && !match[3].str().empty())
        {
            char op = match[2].str()[0];
            double operand = std::stod(match[3].str());
            if (op == '*')
                multiplier *= operand;
            else if (op == '/')
                divisor = operand;
        }

        double result = (multiplier / divisor) * PI;
        return isNegative ? -result : result;
    }

    if (trimmedInput.find('*') != std::string::npos || trimmedInput.find('/') != std::string::npos)
        return NAN;  

    std::istringstream stream(trimmedInput);
    double value;
    if (stream >> value)
        return isNegative ? -value : value;

    return NAN; 
}