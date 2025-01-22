#include "ApplicationHandler.h"

void ApplicationHandler::setMethod(IntegrationMethod method)
{
    this->selectedMethod = method;
}

void ApplicationHandler::setShowGraph(bool x)
{
    this->showGraph = x;
}

void ApplicationHandler::setDeleteTextFiles(bool x)
{
    this->deleteTextFiles = x;
}

void ApplicationHandler::setDeleteGraphs(bool x)
{
    this->deleteGraphs = x;
}

std::string ApplicationHandler::getMethod() const
{
    return this->selectedMethod == IntegrationMethod::SIMPSON
               ? "Simpson"
           : this->selectedMethod == IntegrationMethod::TRAPEZOIDAL
               ? "Trapezoidal"
               : "Both";
}