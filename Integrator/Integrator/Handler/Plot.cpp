#include "ApplicationHandler.h"

void ApplicationHandler::plot(const std::string &title, const std::string &function_name,
                              const std::string &filename_suffix)
{
    std::string configFilename = "plot_config_" + filename_suffix + ".txt";
    std::string imageFilename = "plot_result_" + filename_suffix + ".png";
    std::string intervalFilename = "intervals_log.txt";
    std::string simpsonIntervalFilename = "simpson_intervals_log.txt";
    // I'm aware of how dumb this design is, it will effort to fix it and considering this isn't made for embedded systems it doesn't matter

    std::ofstream configFile(configFilename);
    if (configFile.is_open())
    {
        trackFile(configFilename);
        trackFile(imageFilename);
        trackFile(intervalFilename);
        trackFile(simpsonIntervalFilename);

        configFile << title << "\n";
        configFile << function_name << "\n";
        configFile.close();

        std::string command = "python plot_graph.py \"" + configFilename + "\"";

        int result = system(command.c_str());

        if (result != 0)
            std::cerr << "Error executing Python script. Make sure Python and required libraries are installed.\n";
    }
    else
        std::cerr << "Error opening config file: " << configFilename << "\n";
}

void ApplicationHandler::displayGraphs()
{
    if (selectedMethod == IntegrationMethod::SIMPSON ||
        selectedMethod == IntegrationMethod::BOTH)
    {
        plot("Error vs Tolerance for Adaptive Simpson's Integration",
             "f(x) = tan(x)", "simpson");
    }

    if (selectedMethod == IntegrationMethod::TRAPEZOIDAL ||
        selectedMethod == IntegrationMethod::BOTH)
    {
        plot("Error vs Tolerance for Adaptive Trapezoidal Integration",
             "f(x) = tan(x)", "trap");
    }
}