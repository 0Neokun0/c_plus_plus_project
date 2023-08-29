// Include precompiled header (used in Visual Studio) - this helps improve compilation speed
#include "stdafx.h"

// Standard C++ libraries
#include <iostream>  // Input and output stream functions
#include <fstream>   // File stream functions
#include <string>    // String manipulation functions
#include <vector>    // Dynamic array container
#include <ctime>     // Date and time functions
#include <sstream>   // String stream for string manipulation
#include <iomanip>   // Input/output manipulators (e.g., setw, setfill)
#include <algorithm> // Algorithms for manipulating sequences (e.g., std::find)
#include <chrono>    // Time-related functions
#include <regex>     // Regular expressions for pattern matching

// Define NOMINMAX before including Windows.h to prevent conflicts with min/max macros
#define NOMINMAX
#include <Windows.h> // Windows API functions and data types

// Function to get the current date in "yyyy/mm/dd" format
std::string getCurrentDate()
{
    std::time_t now = std::time(nullptr);
    char dateBuffer[11]; // 10 characters for "yyyy/mm/dd" plus the null terminator
    struct tm localTime;
    localtime_s(&localTime, &now);
    std::strftime(dateBuffer, sizeof(dateBuffer), "%Y/%m/%d", &localTime);

    return dateBuffer;
}

std::string getDatetimeStr()
{
    time_t t = time(nullptr);

    struct tm localTime;
    if (localtime_s(&localTime, &t) != 0)
    {
        // Handle the error if localtime_s fails
        // For example, you could return an empty string or a default value
        return "";
    }

    std::stringstream s;
    s << localTime.tm_year + 1900;
    s << "/" << std::setw(2) << std::setfill('0') << localTime.tm_mon + 1;
    s << "/" << std::setw(2) << std::setfill('0') << localTime.tm_mday;

    return s.str();
}

// Check if a file exists at the given file path
bool fileExists(const std::string &filePath)
{
    std::ifstream file(filePath);
    return file.good(); // Return whether the file is in good state
}

// Find the line containing the main version information in the file
std::string findMainVersionLine(const std::vector<std::string> &fileLines)
{
    for (const std::string &line : fileLines)
    {
        // Check if the line contains "const Vi_Version" and is not commented out or marked as "_Prev"
        if (line.find("const Vi_Version") != std::string::npos &&
            line.find("//") != 0 &&
            line.find("_Prev") == std::string::npos)
        {
            return line; // Return the main version line
        }
    }
    return ""; // Return an empty string if no valid main version line is found
}

// Overloaded function to get the local time in the form of a tm struct
struct tm getLocalTime(const time_t *time)
{
    struct tm localTime;
    localtime_s(&localTime, time);
    return localTime;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

// Function to update the log file with relevant information about changes
void updateLogFile(const std::string &logFilePath, const std::string &fileName, const std::string &mainVersionChange, const std::string &revisionChange)
{
    // Open or create the log file in append mode
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (!logFile)
    {
        // If the file cannot be opened or created, show an error message and return
        std::cerr << "Error: Could not open or create update_log.txt" << std::endl;
        return;
    }

    // Get the current local time in "yyyy-mm-dd HH:MM:SS" format
    std::time_t now = std::time(nullptr);
    struct tm localTime;
    localtime_s(&localTime, &now);

    char currentTimeBuffer[20]; // 19 characters for "yyyy-mm-dd HH:MM:SS" plus the null terminator
    strftime(currentTimeBuffer, sizeof(currentTimeBuffer), "%Y-%m-%d %H:%M:%S", &localTime);
    std::string currentTime = currentTimeBuffer;

    // Write the current local time to the log file
    logFile << currentTime << " ";

    // Write the file name to the log file
    logFile << fileName << " ";

    // Write the main version change information if it's provided
    if (!mainVersionChange.empty())
    {
        logFile << "Main Version Changed: " << mainVersionChange << " ";
    }

    // Write the revision change information if it's provided
    if (!revisionChange.empty())
    {
        logFile << "Revision Changed: " << revisionChange << " ";
    }

    // Write a newline character to end the log entry
    logFile << std::endl;

    // Close the log file
    logFile.close();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

// Function to update the main version in a file
void updateMainVersion(std::vector<std::string> &fileLines, const std::string &filePath, const std::string &fileName)
{
    // Find the current main version line in the list of file lines
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
            // Extract and store elements between quotes
            elements.push_back(mainVersionLine.substr(startPos + 1, endPos - startPos - 1));
            startPos = mainVersionLine.find("\"", endPos + 1);
            endPos = mainVersionLine.find("\"", startPos + 1);
        }

        // Display extracted elements with descriptions
        std::vector<std::string> elementDescriptions(7);
        // Descriptions for each element
        elementDescriptions[0] = "Element: Component";
        elementDescriptions[1] = "Element: Date";
        elementDescriptions[2] = "Element: Main Version";
        elementDescriptions[3] = "Element: Revision";
        elementDescriptions[4] = "Element: Identifier";
        elementDescriptions[5] = "Element: Unknown1";
        elementDescriptions[6] = "Element: Unknown2";

        // Display element descriptions along with their extracted values
        for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
        {
            std::cout << elementDescriptions[i] << ": " << elements[i] << std::endl;
        }

        // Prompt the user for the new main version
        std::string newMainVersion;
        std::cout << "Enter the new main version (3 digits): ";
        std::getline(std::cin, newMainVersion);

        // Validate user input for the new main version
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

            // Create the new version line with updated elements and new main version number
            std::string newVersionLine = mainVersionLine;
            for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
            {
                size_t startPos = newVersionLine.find("\"" + elements[i] + "\"");
                if (startPos != std::string::npos)
                {
                    // Replace existing element value with the corresponding extracted value
                    newVersionLine.replace(startPos, elements[i].length() + 2, "\"" + elements[i] + "\"");
                }
            }

            // Update the Main Version element with the new version number
            size_t versionNumberPos = newVersionLine.find(elements[2]);
            if (versionNumberPos != std::string::npos)
            {
                newVersionLine.replace(versionNumberPos, elements[2].length(), newMainVersion);
            }

            // Remove extra spaces
            size_t pos = newVersionLine.find("  ");
            while (pos != std::string::npos)
            {
                newVersionLine.replace(pos, 2, " ");
                pos = newVersionLine.find("  ", pos);
            }

            // Check if the current revision is greater than "01" and reset if necessary
            size_t currentRevisionPos = newVersionLine.find(elements[3]);
            if (currentRevisionPos != std::string::npos)
            {
                size_t endRevisionPos = newVersionLine.find("\"", currentRevisionPos + 1);
                if (endRevisionPos != std::string::npos)
                {
                    // Extract the current revision value and reset if greater than 1
                    std::string currentRevision = newVersionLine.substr(currentRevisionPos + 1, endRevisionPos - currentRevisionPos - 1);
                    if (std::stoi(currentRevision) > 1)
                    {
                        newVersionLine.replace(currentRevisionPos + 1, endRevisionPos - currentRevisionPos - 1, "01");
                    }
                }
            }

            std::string formattedDate = getDatetimeStr();

            // Update the Date element with the new formatted date
            size_t datePos = newVersionLine.find("\"" + elements[1] + "\"");
            if (datePos != std::string::npos)
            {
                newVersionLine.replace(datePos + 1, elements[1].length(), formattedDate);
            }

            // Correct Identifier element format and update it
            size_t identifierPos = newVersionLine.find(elements[4]);
            if (identifierPos != std::string::npos)
            {
                std::string identifier = elements[4]; // Copy the existing Identifier
                size_t dashPos = identifier.find('-');
                if (dashPos != std::string::npos)
                {
                    // Update the main version part of the Identifier with the new main version
                    identifier.replace(dashPos + 1, 3, newMainVersion);

                    // Update the Identifier's revision number part
                    size_t revisionStartPos = identifier.find('-', dashPos);
                    if (revisionStartPos != std::string::npos)
                    {
                        // Update the revision number in the Identifier
                        identifier.replace(revisionStartPos + 1, 3, "01");
                    }
                }

                // Update the Identifier in the newVersionLine
                newVersionLine.replace(identifierPos, elements[4].length(), identifier);
            }

            // Update the main version number in the newVersionLine
            size_t mainVersionPos = newVersionLine.find(elements[2]);
            if (mainVersionPos != std::string::npos)
            {
                newVersionLine.replace(mainVersionPos, elements[2].length(), newMainVersion);
            }

            // Remove extra spaces from elements
            for (size_t i = 0; i < elements.size(); ++i)
            {
                // Trim spaces at the beginning and end of each element
                size_t startPos = elements[i].find_first_not_of(" ");
                size_t endPos = elements[i].find_last_not_of(" ");
                if (startPos != std::string::npos && endPos != std::string::npos)
                {
                    elements[i] = elements[i].substr(startPos, endPos - startPos + 1);
                }
            }

            // Reset Revision element to "01"
            size_t revisionPos = newVersionLine.find(elements[3]);
            if (revisionPos != std::string::npos)
            {
                newVersionLine.replace(revisionPos, elements[3].length(), "01");
            }

            // Insert the new line below the current main version line
            auto it = std::find(fileLines.begin(), fileLines.end(), mainVersionLine);
            if (it != fileLines.end())
            {
                // Add "_Prev" to the current main version line
                size_t versionPos = it->find("_Version");
                if (versionPos != std::string::npos)
                {
                    size_t parenthesisPos = it->find("(", versionPos);
                    if (parenthesisPos != std::string::npos)
                    {
                        *it = it->substr(0, parenthesisPos - 1) + "_Prev" + it->substr(parenthesisPos - 1);

                        size_t componentStartPos = it->find("\"", parenthesisPos);
                        size_t componentEndPos = it->find("\"", componentStartPos + 1);
                        if (componentStartPos != std::string::npos && componentEndPos != std::string::npos)
                        {
                            std::string component = it->substr(componentStartPos + 1, componentEndPos - componentStartPos - 1);
                            std::string modifiedComponent = component + ".Prev";
                            *it = it->substr(0, componentStartPos + 1) + modifiedComponent + it->substr(componentEndPos);

                            // Remove extra spaces
                            size_t pos = it->find("  ");
                            while (pos != std::string::npos)
                            {
                                it->replace(pos, 2, " ");
                                pos = it->find("  ");
                            }

                            // Trim spaces at the beginning and end of the line
                            size_t startPos = it->find_first_not_of(" ");
                            size_t endPos = it->find_last_not_of(" ");
                            if (startPos != std::string::npos && endPos != std::string::npos)
                            {
                                *it = it->substr(startPos, endPos - startPos + 1);
                            }
                        }
                    }
                }

                // Find the position of the newly added line
                size_t newPos = std::distance(fileLines.begin(), it);

                // Insert the new version line right below the current main version line
                fileLines.insert(fileLines.begin() + newPos + 1, newVersionLine);
            }

            // Inform the user that the main version is updated
            std::cout << "Main version updated to " << newMainVersion << std::endl;

            // Update the log file with the changes made
            std::string directoryPath = filePath.substr(0, filePath.find_last_of("\\/"));
            std::string logMessage = newMainVersion + " -> " + newMainVersion;
            updateLogFile(directoryPath + "\\update_log.txt", fileName, logMessage, "");
        }
        else
        {
            // Inform the user about invalid main version input
            std::cout << "Invalid input for main version. Please enter 3 digits." << std::endl;
        }
    }
    else
    {
        // Inform the user if no valid main version line is found in the file
        std::cout << "No valid main version line found in the file." << std::endl;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

void updateRevision(std::vector<std::string> &fileLines, const std::string &filePath, const std::string &fileName)
{
    // Extract elements from the main version line
    std::string mainVersionLine = findMainVersionLine(fileLines);
    std::vector<std::string> elements;
    size_t startPos = mainVersionLine.find("\"");
    size_t endPos = mainVersionLine.find("\"", startPos + 1);
    while (startPos != std::string::npos && endPos != std::string::npos)
    {
        elements.push_back(mainVersionLine.substr(startPos + 1, endPos - startPos - 1));
        startPos = mainVersionLine.find("\"", endPos + 1);
        endPos = mainVersionLine.find("\"", startPos + 1);
    }

    // Initialize element descriptions using a loop
    std::vector<std::string> elementDescriptions(7);
    // extract first line
    // .append
    elementDescriptions[0] = "Element: Component";
    elementDescriptions[1] = "Element: Date";
    elementDescriptions[2] = "Element: Main Version";
    elementDescriptions[3] = "Element: Revision";
    elementDescriptions[4] = "Element: Identifier";
    elementDescriptions[5] = "Element: Unknown1";
    elementDescriptions[6] = "Element: Unknown2";

    std::cout << "Extracted elements from the main version line:" << std::endl;
    for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
    {
        std::cout << elementDescriptions[i] << ": " << elements[i] << std::endl;
    }

    // Step 4: Extract the revision number
    std::string currentRevision = elements[3]; // Assuming revision is at index 3

    // Step 5: Increment the revision number
    int incrementedRevision = std::stoi(currentRevision) + 1;
    std::string newRevision = (incrementedRevision < 10) ? "0" + std::to_string(incrementedRevision) : std::to_string(incrementedRevision);

    // Step 6: Create the new line with updated revision number and formatted date
    std::string newRevisionLine = mainVersionLine;
    size_t revisionPos = newRevisionLine.find("\"" + currentRevision + "\"");
    if (revisionPos != std::string::npos)
    {
        newRevisionLine.replace(revisionPos + 1, currentRevision.length(), newRevision);
    }

    std::string formattedDate = getDatetimeStr();

    // Update the Date element with the new formatted date
    size_t datePos = newRevisionLine.find("\"" + elements[1] + "\"");
    if (datePos != std::string::npos)
    {
        newRevisionLine.replace(datePos + 1, elements[1].length(), formattedDate);
    }

    // Get the revision number from the new line
    std::string newLineRevision = newRevision;

    // Update the Identifier element
    size_t identifierIndex = 4;                         // Index of the Identifier element in the elements vector
    std::string identifier = elements[identifierIndex]; // Assuming the Identifier element is at index 4

    // Find the revision number in the Identifier
    size_t dashPos = identifier.rfind('-');
    size_t revisionStartPos = dashPos + 1;
    size_t revisionEndPos = identifier.find("\"", revisionStartPos);
    std::string identifierRevision = identifier.substr(revisionStartPos, revisionEndPos - revisionStartPos);

    // Replace the old revision number in the Identifier with the new one from the new line
    identifier.replace(revisionStartPos, revisionEndPos - revisionStartPos, newLineRevision);

    // Update the Identifier line in newRevisionLine
    size_t identifierPos = newRevisionLine.find(elements[identifierIndex]);
    if (identifierPos != std::string::npos)
    {
        size_t endPos = identifierPos + elements[identifierIndex].length();
        newRevisionLine.replace(identifierPos, endPos - identifierPos, identifier);
    }

    // Insert the new revision line below the main version line
    auto it = std::find(fileLines.begin(), fileLines.end(), mainVersionLine);
    if (it != fileLines.end())
    {
        // Calculate the position to insert the new revision line
        size_t insertPos = std::distance(fileLines.begin(), it) + 1;

        // Insert the new revision line
        fileLines.insert(fileLines.begin() + insertPos, newRevisionLine);
    }

    // Step 9: Add comment to the old line
    for (size_t i = 0; i < fileLines.size(); ++i)
    {
        if (fileLines[i].find(mainVersionLine) != std::string::npos)
        {
            fileLines[i] = "//" + fileLines[i]; // Add "//" comment to the old line
            break;
        }
    }

    // Update the log file with the changes made
    std::string logFilePath = filePath.substr(0, filePath.find_last_of("\\/")) + "\\update_log.txt";
    updateLogFile(logFilePath, fileName, "", currentRevision + " -> " + newRevision);

    // Save the updated lines back to the file (as before)
    std::ofstream outputFile(filePath);
    for (const std::string &updatedLine : fileLines)
    {
        outputFile << updatedLine << "\n";
    }
    outputFile.close();

    std::cout << "Revision updated to " << newRevision << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

int main()
{
    // Loop to repeatedly prompt the user for file path and options
    while (true)
    {
        // Prompt the user to enter the file path or quit the program
        std::cout << "Enter the file path (or '0' or 'q' to quit): ";
        std::string filePath;
        std::getline(std::cin, filePath);

        // Check if the user wants to quit the program
        if (filePath == "0" || filePath == "q")
        {
            std::cout << "Quitting the program." << std::endl;
            break;
        }

        // Check if the specified file exists
        if (!fileExists(filePath))
        {
            std::cout << "File not found at the specified path." << std::endl;
            continue; // Skip to the next iteration of the loop
        }

        // Extract the file name from the file path
        std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);

        // Read the contents of the file into a vector of strings (each line as an element)
        std::vector<std::string> fileLines;
        std::string line;
        std::ifstream inputFile(filePath);
        while (std::getline(inputFile, line))
        {
            fileLines.push_back(line);
        }
        inputFile.close();

        // Find the main version line in the file
        std::string mainVersionLine = findMainVersionLine(fileLines);

        // Check if a valid main version line is found
        if (!mainVersionLine.empty())
        {
            std::cout << "File found: " << fileName << std::endl;
            std::cout << "Enter '1' to update main version or '2' to update revision: ";
            int option;
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

            // Check the chosen option
            if (option == 1)
            {
                // Call the function to update the main version
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
                // Call the function to update the revision
                updateRevision(fileLines, filePath, fileName);

                // Write the updated lines back to the file
                std::ofstream outputFile(filePath);
                for (const std::string &updatedLine : fileLines)
                {
                    outputFile << updatedLine << "\n";
                }
                outputFile.close();
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

        // Ask the user if they want to continue or quit the program
        std::cout << "Do you want to continue? (Press '0' or 'q' to quit, any other key to continue): ";
        std::string quitChoice;
        std::getline(std::cin, quitChoice);

        // Check if the user wants to quit the program
        if (quitChoice == "0" || quitChoice == "q")
        {
            std::cout << "Quitting the program." << std::endl;
            break;
        }
    } // End of while loop

    return 0;
}

// Reamaining is date format (50 %)
