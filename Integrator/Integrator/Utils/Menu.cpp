#include "Menu.h"

InteractiveMenu::InteractiveMenu() : selectedOption(0)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    normalColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    highlightTextColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    highlightBgColor = BACKGROUND_BLUE | BACKGROUND_INTENSITY;

    options = {};
    questionText = "Select an option";
}

void InteractiveMenu::setOptions(const std::vector<std::string> &newOptions)
{
    options = newOptions;
}

void InteractiveMenu::setQuestionText(const std::string &text)
{
    questionText = text;
}

void InteractiveMenu::setHighlightColors(WORD textColor, WORD bgColor)
{
    highlightTextColor = textColor;
    highlightBgColor = bgColor;
}

void InteractiveMenu::setColor(WORD textColor, WORD bgColor)
{
    SetConsoleTextAttribute(hConsole, textColor | bgColor);
}

void InteractiveMenu::resetColor()
{
    SetConsoleTextAttribute(hConsole, normalColor);
}

void InteractiveMenu::printMenu()
{
    system("cls");
    std::cout << "\n   " << questionText << "\n\n";

    for (int i = 0; i < options.size(); i++)
    {
        if (i == selectedOption)
        {
            setColor(highlightTextColor, highlightBgColor);
            std::cout << "   --> " << options[i] << std::endl;
            resetColor();
        }
        else
        {
            std::cout << "     " << options[i] << std::endl;
        }
        std::cout << "\n";
    }

    std::cout << "\n   Controls: Up/W = Up   Down/S = Down   Enter = Select\n";
}

int InteractiveMenu::getChoice()
{
    while (true)
    {
        printMenu();
        int key = _getch();

        if (key == 224)
        {
            key = _getch();

            switch (key)
            {
            case 72: // Up
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
                break;
            case 80: // Down
                selectedOption = (selectedOption + 1) % options.size();
                break;
            }
        }
        else if (key == 'w' || key == 'W')
            selectedOption = (selectedOption - 1 + options.size()) % options.size();
        else if (key == 's' || key == 'S')
            selectedOption = (selectedOption + 1) % options.size();
        else if (key == 13) // Enter
            return selectedOption;
    }
}
