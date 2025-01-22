#ifndef Menu_H
#define Menu_H

#include <vector>
#include <Windows.h>
#include <conio.h>
#include <iostream>

class InteractiveMenu
{
private:
    HANDLE hConsole;                  ///< Handle to console for color configuration
    int selectedOption;               ///< Currently selected menu option
    std::vector<std::string> options; ///< List of menu options
    std::string questionText;         ///< Question text displayed above the menu

    WORD normalColor;        ///< Default text color
    WORD highlightTextColor; ///< Highlighted text color
    WORD highlightBgColor;   ///< Highlighted background color

    /**
     * Sets the text and background colors for the console
     * @param textColor Color for the text
     * @param bgColor Color for the background
     */
    void setColor(WORD textColor, WORD bgColor);

    void resetColor();
    void printMenu();

public:
    InteractiveMenu();

    /**
     * Sets the list of menu options
     * @param newOptions List of options to display
     */
    void setOptions(const std::vector<std::string> &newOptions);

    /**
     * Sets the question text displayed above the menu
     * @param text The question text
     */
    void setQuestionText(const std::string &text);

    /**
     * Sets custom highlight colors for the menu
     * @param textColor Highlighted text color
     * @param bgColor Highlighted background color
     */
    void setHighlightColors(WORD textColor, WORD bgColor);

    /**
     * Displays the menu and returns the index of the selected option
     * @return Index of the selected menu option
     */
    int getChoice();
};

#endif // Menu_H