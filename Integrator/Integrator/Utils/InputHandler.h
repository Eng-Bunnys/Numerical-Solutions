#ifndef InputHandler_H
#define InputHandler_H

#include <string>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

class InputHandler
{
public:
    static std::string trimWhitespace(const std::string& str);

    static double parsePiInput(const std::string& input);
};

#endif // InputHandler_H
