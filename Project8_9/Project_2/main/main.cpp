#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype> // For isdigit function

// Function to generate current date and time
std::string getCurrentDateTime()
{
    std::time_t now = std::time(0);
    std::tm *ltm = std::localtime(&now);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return buffer;
}

// Function to get valid 3-digit version number from user
std::string getValidVersionNumber()
{
    std::string version;
    bool validInput = false;

    while (!validInput)
    {
        std::cout << "Enter new version number (3 digits): ";
        std::cin >> version;

        if (version.length() != 3)
        {
            std::cout << "Version number must be exactly 3 digits.\n";
        }
        else
        {
            bool allDigits = true;
            for (char c : version)
            {
                if (!std::isdigit(c))
                {
                    allDigits = false;
                    break;
                }
            }

            if (allDigits)
            {
                validInput = true;
            }
            else
            {
                std::cout << "Version number must contain only digits.\n";
            }
        }
    }

    return version;
}

bool isFirstRun()
{
    std::ifstream logFile("version_change_log.txt");
    return !logFile.good();
}

int main()
{
    std::string version, revision;

    int option;
    bool versionChanged = false;       // Track if version number is changed
    bool revisionChanged = false;      // Track if revision number is changed
    bool addCommentToPrevDate = false; // Track if "// " should be added to previous Date
    bool addPrevToFileNames = false;   // Track if "_Prev" should be added to previous file names

    while (true)
    {
        std::cout << "Choose an option:\n";
        std::cout << "1. Update version\n";
        std::cout << "2. Update revision\n";
        std::cout << "0. Quit\n";
        std::cin >> option;

        if (option == 1)
        {
            version = getValidVersionNumber();
            if (version.length() != 3)
            {
                std::cout << "Version number must be exactly 3 digits.\n";
                continue;
            }

            revision = "01";             // Reset revision to "01" when version is updated
            versionChanged = true;       // Set the versionChanged flag
            addCommentToPrevDate = true; // Set to add "// " to previous Date
            addPrevToFileNames = true;   // Set to add "_Prev" to previous file names
            std::cout << "Changing version number to " << version << ".\n";
            // Mark previous version log line with "// " and "_Prev"
            std::ifstream logFile("version_change_log.txt");
            std::vector<std::string> logLines;
            std::string line;
            bool foundVersionLine = false;
            while (std::getline(logFile, line))
            {
                if (foundVersionLine)
                {
                    line = "// " + line + " _Prev"; // Comment out the previous version line and add "_Prev"
                    foundVersionLine = false;
                }
                if (line.find("Version: " + version) != std::string::npos)
                {
                    foundVersionLine = true;
                }
                logLines.push_back(line);
            }
            logFile.close();

            // Rewrite the log file with updated lines
            std::ofstream outFile("version_change_log.txt");
            for (size_t i = 0; i < logLines.size(); ++i)
            {
                if (i > 0 && logLines[i].find("Date: ") != std::string::npos)
                {
                    if (i == logLines.size() - 1)
                    {
                        outFile << "// " << logLines[i] << '\n'; // Comment out 'Date' for the latest log line
                    }
                    else
                    {
                        outFile << logLines[i] << '\n'; // Keep 'Date' as is for older log lines
                    }
                }
                else if (versionChanged && addPrevToFileNames && logLines[i].find("Updated file: ") != std::string::npos)
                {
                    outFile << logLines[i] << "_Prev" << '\n'; // Add "_Prev" to previous file names
                }
                else
                {
                    outFile << logLines[i] << '\n';
                }
            }
            outFile.close();

            break;
        }
        else if (option == 2)
        {
            // Increment revision number by 1 and format it to 2 digits
            std::ifstream logFile("version_change_log.txt");
            int lastRevision = 0;
            int latestVersion = 0;
            std::string line;
            while (std::getline(logFile, line))
            {
                if (line.find("Revision: ") != std::string::npos)
                {
                    std::size_t foundPos = line.find("Revision: ");
                    std::string revisionStr = line.substr(foundPos + 10, 2);
                    if (!revisionStr.empty() && std::isdigit(revisionStr[0]) && std::isdigit(revisionStr[1]))
                    {
                        lastRevision = std::stoi(revisionStr);
                    }
                }
                if (line.find("Version: ") != std::string::npos)
                {
                    std::size_t foundPos = line.find("Version: ");
                    std::string versionStr = line.substr(foundPos + 9, 3);
                    if (!versionStr.empty() && std::isdigit(versionStr[0]) && std::isdigit(versionStr[1]) && std::isdigit(versionStr[2]))
                    {
                        latestVersion = std::stoi(versionStr);
                    }
                }
            }
            logFile.close();

            lastRevision = (lastRevision + 1) % 100;
            revision = (lastRevision < 10) ? ("0" + std::to_string(lastRevision)) : std::to_string(lastRevision);
            version = (latestVersion > 0) ? std::to_string(latestVersion) : "000";

            revisionChanged = true;      // Set the revisionChanged flag
            addCommentToPrevDate = true; // Set to add "// " to previous Date
            addPrevToFileNames = false;  // Reset to not add "_Prev" to previous file names
            std::cout << "Changing revision number to " << revision << ".\n";

            break;
        }
        else if (option == 0)
        {
            std::cout << "Exiting...\n";
            return 0;
        }
        else
        {
            std::cout << "Invalid option selected. Please try again.\n";
        }
    }
    // Read existing log lines and prepare updated log entry
    std::ifstream logFileIn("version_change_log.txt");
    std::vector<std::string> logLines;
    std::string line;
    while (std::getline(logFileIn, line))
    {
        if (addCommentToPrevDate && line.find("Date: ") == 0)
        {
            line = "// " + line; // Comment out the Date line
            addCommentToPrevDate = false;
        }
        logLines.push_back(line);
    }
    logFileIn.close();

    // Rewrite the log file with updated lines
    std::ofstream logFileOut("version_change_log.txt");
    for (const std::string &logLine : logLines)
    {
        logFileOut << logLine << '\n';
    }
    logFileOut.close();

    // Prepare the log entry for version or revision changes
    std::string logEntry = "Date: " + getCurrentDateTime() + " - Version: " + version + " - Revision: " + revision;

    // Assume you have header file names in a vector
    std::vector<std::string> headerFiles = {"header_1.h", "header_2.h"};
    for (const std::string &header : headerFiles)
    {
        // Add the updated file information to the log entry
        if (versionChanged)
        {
            logEntry += " - Updated file: " + header + " " + version + "-" + revision + "_Prev"; // Add "_Prev" to older versions
        }
        else if (revisionChanged)
        {
            logEntry += " - Updated file: " + header + " " + version + "-" + revision; // No "_Prev" for revision change log line
        }
    }

    // Update version_change_log.txt
    std::ofstream logFile("version_change_log.txt", std::ios_base::app);
    if (!logFile.is_open())
    {
        std::cerr << "Error opening log file." << std::endl;
        return 1;
    }

    logFile << logEntry << "\n\n"; // Write log entry to file
    logFile.close();               // Close the log file

    return 0;
}
