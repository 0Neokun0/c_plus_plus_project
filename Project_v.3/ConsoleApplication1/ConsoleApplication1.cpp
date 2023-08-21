#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>  // Include this for std::stringstream
#include <iomanip>  // Include this for std::setfill and std::setw
#include <algorithm> // Add this line for the all_of function



tm getLocalTime(time_t* timer) {
    tm timeinfo;
#if defined(_WIN32) && _MSC_VER < 1900 // Visual Studio 2013 or earlier
    localtime_s(&timeinfo, timer);
#else
    localtime_s(timer, &timeinfo);
#endif
    return timeinfo;
}


bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

void updateLogFile(const std::string& filePath, const std::string& newMainVersion, const std::string& newRevision) {
    std::string directoryPath = filePath.substr(0, filePath.find_last_of("\\/"));
    std::string logFilePath = directoryPath + "\\update_log.txt";

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
    logFile << filePath << " ";
    logFile << "New Main Version: " << newMainVersion << " ";
    logFile << "New Revision: " << newRevision << std::endl;
    logFile.close();
}


void updateMainVersion(std::vector<std::string>& fileLines, const std::string& newMainVersion) {
    for (size_t i = 0; i < fileLines.size(); ++i) {
        std::string& line = fileLines[i];

        // Check if the line contains "const Vi_Version"
        if (line.find("const Vi_Version") != std::string::npos) {
            std::string prefix = "_Prev";  // Prefix for lines with "_Prev"
            size_t prefixPos = line.find(prefix);

            // Check if the line contains the specified prefix
            if (prefixPos != std::string::npos) {
                // Find the positions of the main version number within the line
                size_t startPos = line.find('"', prefixPos + prefix.length()) + 1;
                size_t endPos = line.find('"', startPos);
                std::string mainVersion = line.substr(startPos, endPos - startPos);

                // Check if the new main version is already present in the line
                if (mainVersion == newMainVersion) {
                    // Prompt the user to enter a different main version
                    std::cout << "Main version " << newMainVersion << " already exists. Enter a different version: ";
                    std::string userInputVersion;
                    std::getline(std::cin, userInputVersion);  // Get user input for a different version

                    // Reset the input stream and ignore any remaining characters
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // Retry the function with the new user input
                    updateMainVersion(fileLines, userInputVersion);
                    return;  // Exit the function after retry
                }

                // Comment out the original line and add the new main version line
                std::string commentedLine = "//" + line;
                std::string newMainVersionLine = line.substr(0, startPos) + newMainVersion + line.substr(endPos);
                fileLines[i] = commentedLine;  // Replace the original line with the commented line
                fileLines.insert(fileLines.begin() + i + 1, newMainVersionLine);  // Insert the new line

                // Reset the revision number in the original line
                size_t revStartPos = line.find_last_of('"') - 1;
                size_t revEndPos = line.find_last_of('"');
                line.replace(revStartPos, revEndPos - revStartPos, "01");

                break;  // Exit the loop after processing the line
            }
        }
    }
}



void updateRevision(std::vector<std::string>& fileLines, const std::string& filePath, const std::string& newMainVersion = "") {
    for (size_t i = 0; i < fileLines.size(); ++i) {
        std::string& line = fileLines[i];

        if (line.find("const Vi_Version") != std::string::npos) {
            std::string prefix = "_Prev";
            size_t prefixPos = line.find(prefix);

            if (prefixPos == std::string::npos) {
                size_t revStartPos = line.find_last_of('"') - 1;
                size_t revEndPos = line.find_last_of('"');
                
                if (revStartPos != std::string::npos && revEndPos != std::string::npos && revEndPos > revStartPos) {
                    std::string revision = line.substr(revStartPos, revEndPos - revStartPos);

                    try {
                        int revisionNumber = std::stoi(revision);
                        revisionNumber++;
                        std::stringstream newRevision;
                        newRevision << std::setfill('0') << std::setw(2) << revisionNumber;
                        line.replace(revStartPos, revEndPos - revStartPos, newRevision.str());

                        size_t mainVersionStartPos = line.find('"', line.find('"') + 1) + 1;
                        size_t mainVersionEndPos = line.find('"', mainVersionStartPos);
                        if (mainVersionStartPos != std::string::npos && mainVersionEndPos != std::string::npos && mainVersionEndPos > mainVersionStartPos) {
                            std::string mainVersion = line.substr(mainVersionStartPos, mainVersionEndPos - mainVersionStartPos);
                            std::string newLine = line;
                            newLine.replace(mainVersionStartPos, mainVersionEndPos - mainVersionStartPos, newRevision.str());

                            fileLines.insert(fileLines.begin() + i + 1, newLine);
                            std::string commentedLine = "//" + line;
                            fileLines.insert(fileLines.begin() + i + 2, commentedLine);

                            updateLogFile(filePath, newMainVersion.empty() ? "new_main_version" : newMainVersion, newRevision.str());

                            break;
                        }
                    } catch (const std::invalid_argument& ex) {
                        std::cerr << "Invalid argument for revision: " << ex.what() << std::endl;
						std::cerr << "Line content: " << line << std::endl;
						std::cerr << "revStartPos: " << revStartPos << ", revEndPos: " << revEndPos << std::endl;
						return;  // Exit the function since conversion failed
                    }
                }
            }
        }
    }
}



int main() {
	// Log the version change at the beginning of the program
    updateLogFile("path_to_input_file", "new_main_version", "new_revision");

    while (true) {
        std::cout << "Enter the file path (or '0' or 'q' to quit): ";
        std::string filePath;
        std::getline(std::cin, filePath);

        if (filePath == "0" || filePath == "q") {
            std::cout << "Quitting the program." << std::endl;
            break;
        }

        std::ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            std::cout << "File not found at the specified path." << std::endl;
            continue;
        }

        std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);

        std::string line;
        std::vector<std::string> fileLines;
        while (std::getline(inputFile, line)) {
            fileLines.push_back(line);
        }

        inputFile.close();

        std::cout << "File found: " << fileName << std::endl;
        std::cout << "Enter '1' to update main version or '2' to update revision: ";
        int option;
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        if (option == 1) {
            std::cout << "Enter the new main version (3 digits): ";
            std::string newMainVersion;
            std::getline(std::cin, newMainVersion);

            if (newMainVersion.length() != 3 || !std::all_of(newMainVersion.begin(), newMainVersion.end(), ::isdigit)) {
                std::cout << "Invalid input for main version. Please enter 3 digits." << std::endl;
            } else {
                for (std::string& fileLine : fileLines) {
                    if (fileLine.find("const Vi_Version") != std::string::npos) {
                        size_t startPos = fileLine.find('"', fileLine.find_last_of('"') - 2) + 1;
                        size_t endPos = fileLine.find('"', startPos);
                        std::string mainVersion = fileLine.substr(startPos, endPos - startPos);


                        // Create variables for each part of the line
                        std::string name, date, revision, dummy1, dummy2, dummy3, hp;
                        std::istringstream iss(fileLine);
                        iss >> dummy1 >> dummy2 >> name >> date >> revision >> dummy3 >> hp;

						// Update main version and recreate the line
						mainVersion = newMainVersion;
						std::stringstream updatedLine;
						updatedLine << "const Vi_Version " << name << " (        \"" << name << "\",         \"" << date << "\", \"" << mainVersion << "\", \"01\", \"" << dummy3 << "\", \"\", \"" << hp << "\");";
						fileLine = updatedLine.str();
						break;


                    }
                }

                std::ofstream outputFile(filePath);
                for (const std::string& updatedLine : fileLines) {
                    outputFile << updatedLine << "\n";
                }
                outputFile.close();

                updateLogFile(filePath, newMainVersion, "01");

                std::cout << "Main version has been updated to " << newMainVersion << " for file " << fileName << std::endl;
            }
       } else if (option == 2) {
			updateRevision(fileLines, filePath);
            updateLogFile(filePath, "new_main_version", "new_revision");
        } else {
            std::cout << "Invalid option. Please select '1' or '2'." << std::endl;
            continue;
        }

        std::cout << "Do you want to continue? (Press '0' or 'q' to quit, any other key to continue): ";
        std::string quitChoice;
        std::getline(std::cin, quitChoice);

        if (quitChoice == "0" || quitChoice == "q") {
            std::cout << "Quitting the program." << std::endl;
            break;
        }
    }

    return 0;
}