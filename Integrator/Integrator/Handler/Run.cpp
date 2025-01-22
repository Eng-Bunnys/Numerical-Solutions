#include "ApplicationHandler.h"
#include "../Utils/Menu.h"

void ApplicationHandler::printWelcomeMessage()
{
    std::cout << "Welcome to Integrator!" << std::endl;
}

void ApplicationHandler::printSettings()
{
    system("cls");
    std::cout << "=================== User Settings ===================\n";
    std::cout << "Integration Method: " << getMethod() << "\n";
    std::cout << "Delete Text Files: " << (deleteTextFiles ? "Yes" : "No") << "\n";
    std::cout << "Delete Graph Images: " << (deleteGraphs ? "Yes" : "No") << "\n";
    std::cout << "Print Graphs: " << (showGraph ? "Yes" : "No") << "\n";
    std::cout << "Show Exact Result: " << (showExact ? "Yes" : "No") << "\n";  // Add this line
    std::cout << "====================================================\n\n";
}

void ApplicationHandler::selectIntegrationMethod()
{
    InteractiveMenu menu;
    menu.setHighlightColors(
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    menu.setOptions({"Simpson's method", "Trapezoidal method", "Both methods"});
    menu.setQuestionText("Select an integration method:");

    int choice = menu.getChoice();
    switch (choice)
    {
    case 0:
        setMethod(IntegrationMethod::SIMPSON);
        break;
    case 1:
        setMethod(IntegrationMethod::TRAPEZOIDAL);
        break;
    case 2:
        setMethod(IntegrationMethod::BOTH);
        break;
    }
}

void ApplicationHandler::askSettings()
{
    InteractiveMenu menu;
    menu.setHighlightColors(
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    menu.setOptions({ "Yes", "No" });
    menu.setQuestionText("Would you like to delete text files after completion?");
    deleteTextFiles = (menu.getChoice() == 0);
    menu.setQuestionText("Would you like to delete graph images after completion?");
    deleteGraphs = (menu.getChoice() == 0);
    menu.setQuestionText("Would you like to print graphs?");
    showGraph = (menu.getChoice() == 0);
    menu.setQuestionText("Would you like to show exact results?"); 
    showExact = (menu.getChoice() == 0);
}

void ApplicationHandler::run()
{
    printWelcomeMessage();

    selectIntegrationMethod();

    askSettings();

    printSettings();

    handleSingleCalculation();

    std::cout << "\nThank you for using the integrator!\nPress any button to exit...\n";

    cleanUpFiles();

    (void)_getch();
}