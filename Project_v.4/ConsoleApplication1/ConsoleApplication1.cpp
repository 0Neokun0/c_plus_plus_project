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
#include <regex>

bool fileExists(const std::string &filePath)
{
    std::ifstream file(filePath);
    return file.good(); // Return whether the file is in good state
}

std::string findMainVersionLine(const std::vector<std::string> &fileLines)
{
    for (const std::string &line : fileLines)
    {
        if (line.find("const Vi_Version") != std::string::npos &&
            line.find("//") != 0 &&
            line.find("_Prev") == std::string::npos)
        {
            return line;
        }
    }
    return "";
}

tm getLocalTime(time_t *timer)
{
    tm timeinfo;
#if defined(_WIN32) && _MSC_VER < 1900
    localtime_s(&timeinfo, timer);
#else
    localtime_s(timer, &timeinfo);
#endif
    return timeinfo; // Return the timeinfo struct
}

struct tm getLocalTime(const time_t *time)
{
    struct tm localTime;
    localtime_s(&localTime, time);
    return localTime;
}

void updateLogFile(const std::string &logFilePath, const std::string &fileName, const std::string &mainVersionChange, const std::string &revisionChange)
{
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (!logFile)
    {
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
    if (!mainVersionChange.empty())
    {
        logFile << "Main Version Changed: " << mainVersionChange << " ";
    }
    if (!revisionChange.empty())
    {
        logFile << "Revision Changed: " << revisionChange << " ";
    }
    logFile << std::endl;

    logFile.close();
}

void updateMainVersion(std::vector<std::string> &fileLines, const std::string &filePath, const std::string &fileName)
{
    std::string mainVersionLine = findMainVersionLine(fileLines);
    if (!mainVersionLine.empty())
    {
        std::cout << "Current Main Version Line: " << mainVersionLine << std::endl;

        // Extract elements inside ""
        std::vector<std::string> elements;
        size_t startPos = mainVersionLine.find("\"");
        size_t endPos = mainVersionLine.find("\"", startPos + 1);
        while (startPos != std::string::npos && endPos != std::string::npos)
        {
            elements.push_back(mainVersionLine.substr(startPos + 1, endPos - startPos - 1));
            startPos = mainVersionLine.find("\"", endPos + 1);
            endPos = mainVersionLine.find("\"", startPos + 1);
        }

        // Display extracted elements with descriptions
        std::vector<std::string> elementDescriptions(7);
        elementDescriptions[0] = "Element: Component";
        elementDescriptions[1] = "Element: Date";
        elementDescriptions[2] = "Element: Main Version";
        elementDescriptions[3] = "Element: Revision";
        elementDescriptions[4] = "Element: Identifier";
        elementDescriptions[5] = "Element: Unknown1";
        elementDescriptions[6] = "Element: Unknown2";

        for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
        {
            std::cout << elementDescriptions[i] << ": " << elements[i] << std::endl;
        }

        // Prompt the user for the new main version
        std::string newMainVersion;
        std::cout << "Enter the new main version (3 digits): ";
        std::getline(std::cin, newMainVersion);

        if (newMainVersion.length() == 3 && std::all_of(newMainVersion.begin(), newMainVersion.end(), ::isdigit))
        {
            // Comment out existing lines with "_Prev" by adding '// ' in front of them
            for (std::string &line : fileLines)
            {
                if (line.find("_Prev") != std::string::npos && line.find("//") != 0)
                {
                    line = "// " + line;
                }
            }

            // Create the new line with updated elements and new main version number
            std::string newVersionLine = mainVersionLine;
            for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
            {
                size_t startPos = newVersionLine.find("\"" + elements[i] + "\"");
                if (startPos != std::string::npos)
                {
                    newVersionLine.replace(startPos, elements[i].length() + 2, "\"" + elements[i] + "\"");
                }
            }

            // Update Main Version element
            size_t versionNumberPos = newVersionLine.find(elements[2]);
            if (versionNumberPos != std::string::npos)
            {
                newVersionLine.replace(versionNumberPos, elements[2].length(), newMainVersion);
            }

			// Reset Revision element to "01"
			size_t revisionPos = newVersionLine.find(elements[3]);
			if (revisionPos != std::string::npos) {
				newVersionLine.replace(revisionPos, elements[3].length(), "01");
			}

			// Reset Identifier element with new main version and revision
			size_t identifierPos = newVersionLine.find(elements[4]);
			if (identifierPos != std::string::npos) {
				std::string identifier = elements[4];
				size_t dashPos = identifier.find('-');
				if (dashPos != std::string::npos) {
					// Update the identifier to include the main version and reset revision
					identifier = "RELS_" + elements[0] + "_" + newMainVersion + "-01\"";
					newVersionLine.replace(identifierPos, elements[4].length(), identifier);
				}
			}


            // Replace Date element with current date
            size_t datePos = newVersionLine.find(elements[1]);
            if (datePos != std::string::npos)
            {
                std::string currentDate = elements[1];
                auto now = std::chrono::system_clock::now();
                std::time_t time = std::chrono::system_clock::to_time_t(now);
                std::tm timeinfo = getLocalTime(&time);
                std::ostringstream formattedDate;
                formattedDate << std::put_time(&timeinfo, "\"%Y/%m/%d\"");
                newVersionLine.replace(datePos, currentDate.length(), formattedDate.str());
            }

            // Replace Identifier element with correct format
            size_t identifierStartPos = newVersionLine.find("\"" + elements[4]);
            if (identifierStartPos != std::string::npos)
            {
                size_t identifierEndPos = newVersionLine.find("\"", identifierStartPos + 1);
                if (identifierEndPos != std::string::npos)
                {
                    newVersionLine.replace(identifierStartPos, identifierEndPos - identifierStartPos + 1, "\"" + elements[4]);
                }
            }

            // Insert the new line below the current main version line
            auto it = std::find(fileLines.begin(), fileLines.end(), mainVersionLine);
            if (it != fileLines.end())
            {
                fileLines.insert(it + 1, newVersionLine);
            }

            std::cout << "Main version updated to " << newMainVersion << std::endl;

            // Update the log file
            std::string directoryPath = filePath.substr(0, filePath.find_last_of("\\/"));
            updateLogFile(directoryPath + "\\update_log.txt", fileName, newMainVersion, "");
        }
        else
        {
            std::cout << "Invalid input for main version. Please enter 3 digits." << std::endl;
        }
    }
    else
    {
        std::cout << "No valid main version line found in the file." << std::endl;
    }
}

int main()
{
    while (true)
    {
        std::cout << "Enter the file path (or '0' or 'q' to quit): ";
        std::string filePath;
        std::getline(std::cin, filePath);

        if (filePath == "0" || filePath == "q")
        {
            std::cout << "Quitting the program." << std::endl;
            break;
        }

        if (!fileExists(filePath))
        {
            std::cout << "File not found at the specified path." << std::endl;
            continue;
        }

        std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
        std::vector<std::string> fileLines;
        std::string line;

        std::ifstream inputFile(filePath);
        while (std::getline(inputFile, line))
        {
            fileLines.push_back(line);
        }
        inputFile.close();

        std::string mainVersionLine = findMainVersionLine(fileLines);
        if (!mainVersionLine.empty())
        {
            std::cout << "File found: " << fileName << std::endl;
            std::cout << "Enter '1' to update main version or '2' to update revision: ";
            int option;
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (option == 1)
            {
                updateMainVersion(fileLines, filePath, fileName);

                // Write the updated lines back to the file
                std::ofstream outputFile(filePath);
                for (const std::string &updatedLine : fileLines)
                {
                    outputFile << updatedLine << "\n";
                }
                outputFile.close();

                // Update the main version line after the file has been modified
                mainVersionLine = findMainVersionLine(fileLines);
            }
            else if (option == 2)
            {
                // ... (code for updating revision)
            }
            else
            {
                std::cout << "Invalid option. Please select '1' or '2'." << std::endl;
            }
        }
        else
        {
            std::cout << "No valid main version line found in the file." << std::endl;
        }

        std::cout << "Do you want to continue? (Press '0' or 'q' to quit, any other key to continue): ";
        std::string quitChoice;
        std::getline(std::cin, quitChoice);

        if (quitChoice == "0" || quitChoice == "q")
        {
            std::cout << "Quitting the program." << std::endl;
            break;
        }
    } // End of while loop

    return 0;
}
