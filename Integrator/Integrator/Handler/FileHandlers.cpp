#include "ApplicationHandler.h"

void ApplicationHandler::trackFile(const std::string &filename)
{
    generatedFiles.push_back(filename);
}

void ApplicationHandler::cleanUpFiles()
{
    for (const auto &filename : generatedFiles)
    {
        bool shouldDelete = false;

        if (filename.find(".txt") != std::string::npos && deleteTextFiles)
            shouldDelete = true;

        else if ((filename.find(".png") != std::string::npos) &&
                 deleteGraphs)
            shouldDelete = true;

        if (shouldDelete && std::remove(filename.c_str()) != 0)
            std::cerr << "Error deleting file: " << filename << std::endl;
    }
    generatedFiles.clear();
}

void ApplicationHandler::generateDataFile(const std::string &filename,
                                          const double *tolerances, const double *results,
                                          const double *errors, const int *subintervals,
                                          int numTolerances)
{
    std::ofstream dataFile(filename);
    if (dataFile.is_open())
    {
        trackFile(filename);
        for (int i = 0; i < numTolerances; i++)
            dataFile << tolerances[i] << " " << subintervals[i] << " "
                     << results[i] << " " << errors[i] << "\n";

        dataFile.close();
    }
    else
    {
        std::cerr << "Error opening " << filename << "\n";
    }
}