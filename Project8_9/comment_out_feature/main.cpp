#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>

void commentOutPreviousLogs(const std::string& fileName) {
    std::ifstream logFileIn(fileName);
    if (logFileIn.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(logFileIn, line)) {
            lines.push_back("// " + line);
        }
        logFileIn.close();

        std::ofstream logFileOut(fileName);
        if (logFileOut.is_open()) {
            for (const auto& commentedLine : lines) {
                logFileOut << commentedLine << "\n";
            }
            logFileOut.close();
        }
    }
}

int main() {
    // Get user input
    int userInput;
    std::cout << "Enter three digits without spaces: ";
    std::cin >> userInput;

    // Extract individual digits
    int digit1 = userInput / 100;
    int digit2 = (userInput / 10) % 10;
    int digit3 = userInput % 10;

    // Get current date and time
    std::time_t now = std::time(0);
    std::tm* timeInfo = std::localtime(&now);

    // Comment out previous log entries
    commentOutPreviousLogs("log_update.txt");

    // Create log entry
    std::ofstream logFile("log_update.txt", std::ios_base::app);
    if (logFile.is_open()) {
        std::ostringstream logEntry;
        logEntry << "File Name: log_update.txt, "
                 << "Date: " << (timeInfo->tm_year + 1900) << "-" << (timeInfo->tm_mon + 1) << "-" << timeInfo->tm_mday << ", "
                 << "Time: " << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << ", "
                 << "Digits: " << digit1 << " " << digit2 << " " << digit3;

        logFile << logEntry.str() << "\n";
        logFile.close();
        std::cout << "Log entry added to log_update.txt" << std::endl;
    } else {
        std::cerr << "Unable to open log_update.txt for writing." << std::endl;
    }

    return 0;
}
