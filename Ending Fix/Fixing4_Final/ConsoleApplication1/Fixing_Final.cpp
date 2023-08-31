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
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

void updateMainVersion(std::vector<std::string> &fileLines, const std::string &filePath, const std::string &fileName)
{
    std::string newVersionLine;

    // Step 1: Find the current main version line in the list of file lines
    std::string currentMainVersionLine = findMainVersionLine(fileLines);
    if (!currentMainVersionLine.empty() && currentMainVersionLine.find("_Prev") == std::string::npos)
    {
        std::cout << "Current Main Version Line: " << currentMainVersionLine << std::endl;

        // Extract elements inside ""
        std::vector<std::string> elements;
        size_t startPos = currentMainVersionLine.find("\"");
        size_t endPos = currentMainVersionLine.find("\"", startPos + 1);
        while (startPos != std::string::npos && endPos != std::string::npos)
        {
            // Extract and store elements between quotes
            elements.push_back(currentMainVersionLine.substr(startPos + 1, endPos - startPos - 1));
            startPos = currentMainVersionLine.find("\"", endPos + 1);
            endPos = currentMainVersionLine.find("\"", startPos + 1);
        }

        // Descriptions for each element
        std::vector<std::string> elementDescriptions(7);
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

        // Step 2: Extract the current main version and revision numbers from the main version line
        std::string mainVersionFromLine;
        std::string revisionFromLine;

        size_t mainVersionPos = currentMainVersionLine.find("\"" + elements[2] + "\"");
        size_t revisionPos = currentMainVersionLine.find("\"" + elements[3] + "\"");

        if (mainVersionPos != std::string::npos)
        {
            mainVersionFromLine = elements[2]; // Save the current main version number
        }
        if (revisionPos != std::string::npos)
        {
            revisionFromLine = elements[3]; // Save the current revision number
        }

        // Display the current main version and revision numbers
        std::cout << "Current Main Version: " << mainVersionFromLine << std::endl;
        std::cout << "Current Revision: " << revisionFromLine << std::endl;

        // Step 3: Find the main version number (3 digits) and ensure the revision number is 2 digits
        std::string newMainVersion;
        std::cout << "Enter the new main version (3 digits): ";
        std::getline(std::cin, newMainVersion);

        std::string newRevision;
        if (newMainVersion.length() == 3 && std::all_of(newMainVersion.begin(), newMainVersion.end(), ::isdigit))
        {
            newRevision = revisionFromLine;
        }
        else
        {
            newRevision = "01"; // Reset to "01" if not valid
        }

        std::cout << "New Main Version: " << newMainVersion << std::endl;
        std::cout << "New Revision: " << newRevision << std::endl;

        // Step 4: Extract the identifier prefix from the current main version line
        // Extract the identifier prefix from the current main version line
        std::string identifierPrefix;
        size_t identifierStartPos = elements[4].find("RELS_");
        if (identifierStartPos != std::string::npos)
        {
            identifierStartPos += sizeof("RELS_") - 1; // Move past "RELS_" to the identifier prefix
            size_t identifierEndPos = elements[4].find("-", identifierStartPos);
            if (identifierEndPos != std::string::npos)
            {
                identifierPrefix = elements[4].substr(identifierStartPos, identifierEndPos - identifierStartPos) + "_";

                // Print the extracted identifier prefix for debugging
                std::cout << "Extracted Identifier Prefix: " << identifierPrefix << std::endl;
            }
        }

        // Construct the new main version line with updated main version, revision numbers, and modified identifier
std::string currentDate = getCurrentDate();

// Remove any leading zeros from newMainVersion
while (newMainVersion.length() > 1 && newMainVersion[0] == '0')
{
    newMainVersion.erase(0, 1);
}

   // Replace the main version in the identifier with the new main version number
        std::string modifiedIdentifier = "RELS_" + identifierPrefix + newMainVersion + "-" + newRevision;
        size_t identifierDashPos = modifiedIdentifier.find('-');
        if (identifierDashPos != std::string::npos)
        {
            modifiedIdentifier = modifiedIdentifier.substr(0, identifierDashPos + 1) + newRevision;
        }

        // Construct the new main version line with updated main version, revision numbers, and modified identifier
        std::string newMainVersionLine = "const Vi_Version " + elements[0] + "_Version( \"" + elements[0] + "\", \"" + currentDate + "\", \"" +
                                         newMainVersion + "\", \"" + newRevision + "\", \"" + modifiedIdentifier + "\", \"" +
                                         elements[5] + "\", \"" + elements[6] + "\");";

        // Find the position of the current main version line
        size_t currentMainVersionPos = 0;
        for (size_t i = 0; i < fileLines.size(); ++i)
        {
            if (fileLines[i] == currentMainVersionLine)
            {
                currentMainVersionPos = i;
                break;
            }
        }

        // Insert the new main version line below the current main version line
        fileLines.insert(fileLines.begin() + currentMainVersionPos + 1, newMainVersionLine);

        // Add "//" to lines containing "_Prev" and ".Prev"
        for (std::string &line : fileLines)
        {
            if ((line.find("_Prev") != std::string::npos || line.find(".Prev") != std::string::npos) && line.find("//") != 0)
            {
                line = "//" + line;
            }
        }

        // Add "_Prev" to the current main version line
        auto it = std::find(fileLines.begin(), fileLines.end(), currentMainVersionLine);
        size_t versionPos = it->find("_Version");
        if (versionPos != std::string::npos)
        {
            size_t parenthesisPos = it->find("(", versionPos);
            if (parenthesisPos != std::string::npos)
            {
                *it = it->substr(0, parenthesisPos - 1) + "_Prev" + it->substr(parenthesisPos - 1);

                // Append ".Prev" to the component name
                size_t componentStartPos = it->find("\"", parenthesisPos);
                size_t componentEndPos = it->find("\"", componentStartPos + 1);
                if (componentStartPos != std::string::npos && componentEndPos != std::string::npos)
                {
                    std::string component = it->substr(componentStartPos + 1, componentEndPos - componentStartPos - 1);
                    component = trim(component);
                    std::string modifiedComponent = component + ".Prev";
                    *it = it->substr(0, componentStartPos + 1) + modifiedComponent + it->substr(componentEndPos);
                }

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

        // Update the log file with the changes made
        std::string logFilePath = filePath.substr(0, filePath.find_last_of("\\/")) + "\\update_log.txt";
        updateLogFile(logFilePath, fileName, currentMainVersionLine, newMainVersionLine);

        // Display the new main version line
        std::cout << "New Main Version Line: " << newMainVersionLine << std::endl;
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

    // Update the Date element with the new formatted date
    size_t datePos = newRevisionLine.find("\"" + elements[1] + "\"");
    if (datePos != std::string::npos)
    {
        std::string currentDate = getCurrentDate();
        newRevisionLine.replace(datePos + 1, elements[1].length(), currentDate);
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

    // Display the updated revision line again after logging
    std::cout << "Updated Revision Line (after logging): " << newRevisionLine << std::endl;

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