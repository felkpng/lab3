#pragma once
#include "logger.h"
#include <iostream>
#include <fstream>
#include <string>

static std::ofstream logFile("logs.txt", std::ios::app);

void LogInput(const std::string& input) {
    if (logFile.is_open()) {
        logFile << input << std::endl;
        logFile.flush();
    }
}

std::string LoggedInput() {
    std::string input;
    std::getline(std::cin, input);
    LogInput(input);
    return input;
}