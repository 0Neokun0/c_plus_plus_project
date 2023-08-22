#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono> // Add this include for getting the current date

bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good(); // Return whether the file is in good state
}

std::string findMainVersionLine(const std::vector<std::string>& fileLines) {
    for (const std::string& line : fileLines) {
        if (line.find("const Vi_Version") != std::string::npos &&
            line.find("//") != 0 &&
            line.find("_Prev") == std::string::npos) {
            return line;
        }
    }
    return "";
}

tm getLocalTime(time_t* timer) {
    tm timeinfo;
#if defined(_WIN32) && _MSC_VER < 1900
    localtime_s(&timeinfo, timer);
#else
    localtime_s(timer, &timeinfo);
#endif
    return timeinfo; // Return the timeinfo struct
}

void updateLogFile(const std::string& logFilePath, const std::string& fileName, const std::string& mainVersionChange, const std::string& revisionChange) {
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (!logFile) {
        std::cerr << "Error: Could not open or create update_log.txt" << std::endl;
        return;
    }

    std::time_t now = std::time(nullptr);
    struct tm localTime;
#if defined(_WIN32) && _MSC_VER < 1900
    localtime_s(&localTime, &now);
#else
    localtime_s(&now, &localTime);
#endif

    logFile << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " ";
    logFile << fileName << " ";
    if (!mainVersionChange.empty()) {
        logFile << "Main Version Changed: " << mainVersionChange << " ";
    }
    if (!revisionChange.empty()) {
        logFile << "Revision Changed: " << revisionChange << " ";
    }
    logFile << std::endl;

    logFile.close();
}

void updateMainVersion(std::vector<std::string>& fileLines, const std::string& filePath, const std::string& fileName) {
    std::string mainVersionLine = findMainVersionLine(fileLines);
    if (!mainVersionLine.empty()) {
        std::cout << "Current Main Version Line: " << mainVersionLine << std::endl;

        std::cout << "Enter the new main version (3 digits): ";
        std::string newMainVersion;
        std::getline(std::cin, newMainVersion);

        if (newMainVersion.length() == 3 && std::all_of(newMainVersion.begin(), newMainVersion.end(), ::isdigit)) {
            // Check if the current main version line already contains "_Prev"
            bool hasPrev = (mainVersionLine.find("_Prev") != std::string::npos);

            // Comment out existing lines with "_Prev" by adding '// ' in front of them
            for (std::string& line : fileLines) {
                if (line.find("_Prev") != std::string::npos && line.find("//") != 0) {
                    line = "// " + line;
                }
            }

            // Create the new line with the updated main version number and current date
            auto now = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(now);
            std::tm timeinfo = getLocalTime(&time);
            std::ostringstream formattedDate;
            formattedDate << std::put_time(&timeinfo, "\"%Y/%m/%d\"");

            // Create the new line by copying the format of the current main version line
            std::string newVersionLine = mainVersionLine;
            size_t datePos = newVersionLine.find("\"date\"");
            if (datePos != std::string::npos) {
                newVersionLine.replace(datePos, 8, formattedDate.str());
            }
            size_t versionNumberPos = newVersionLine.find("000");
            if (versionNumberPos != std::string::npos) {
                newVersionLine.replace(versionNumberPos, 3, newMainVersion);
            }

            // Insert the new line below the current main version line
            auto it = std::find(fileLines.begin(), fileLines.end(), mainVersionLine);
            if (it != fileLines.end()) {
                fileLines.insert(it + 1, newVersionLine);
            }

            std::cout << "Main version updated to " << newMainVersion << std::endl;

            // Update the log file
            std::string directoryPath = filePath.substr(0, filePath.find_last_of("\\/"));
            updateLogFile(directoryPath + "\\update_log.txt", fileName, newMainVersion, "");
        } else {
            std::cout << "Invalid input for main version. Please enter 3 digits." << std::endl;
        }
    } else {
        std::cout << "No valid main version line found in the file." << std::endl;
    }
}

int main() {
    while (true) {
        std::cout << "Enter the file path (or '0' or 'q' to quit): ";
        std::string filePath;
        std::getline(std::cin, filePath);

        if (filePath == "0" || filePath == "q") {
            std::cout << "Quitting the program." << std::endl;
            break;
        }

        if (!fileExists(filePath)) {
            std::cout << "File not found at the specified path." << std::endl;
            continue;
        }

        std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
        std::vector<std::string> fileLines;
        std::string line;

        std::ifstream inputFile(filePath);
        while (std::getline(inputFile, line)) {
            fileLines.push_back(line);
        }
        inputFile.close();

        std::string mainVersionLine = findMainVersionLine(fileLines);
        if (!mainVersionLine.empty()) {
            std::cout << "File found: " << fileName << std::endl;
            std::cout << "Enter '1' to update main version or '2' to update revision: ";
            int option;
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (option == 1) {
                updateMainVersion(fileLines, filePath, fileName);

                // Write the updated lines back to the file
                std::ofstream outputFile(filePath);
                for (const std::string& updatedLine : fileLines) {
                    outputFile << updatedLine << "\n";
                }
                outputFile.close();

                // Update the main version line after the file has been modified
                mainVersionLine = findMainVersionLine(fileLines);
            } else if (option == 2) {
                // ... (code for updating revision)
            } else {
                std::cout << "Invalid option. Please select '1' or '2'." << std::endl;
            }
        } else {
            std::cout << "No valid main version line found in the file." << std::endl;
        }

        std::cout << "Do you want to continue? (Press '0' or 'q' to quit, any other key to continue): ";
        std::string quitChoice;
        std::getline(std::cin, quitChoice);

        if (quitChoice == "0" || quitChoice == "q") {
            std::cout << "Quitting the program." << std::endl;
            break;
        }
    } // End of while loop

    return 0;
}
