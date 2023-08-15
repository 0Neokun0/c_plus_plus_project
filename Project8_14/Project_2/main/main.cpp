#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

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

// Function to update the log file with formatted lines
void updateLogFile(const std::vector<std::string> &logLines)
{
    std::ofstream outFile("version_change_log.txt");
    for (const std::string &logLine : logLines)
    {
        outFile << logLine << '\n';
    }
    outFile.close();
}

int main()
{
    if (isFirstRun())
    {
        std::ofstream logFile("version_change_log.txt");
        if (logFile.is_open())
        {
            logFile << "This is the log system for version change and revision change.\n\n";
            logFile.close();
        }
        else
        {
            std::cerr << "Error creating log file." << std::endl;
            return 1;
        }
    }

    while (true)
    {
        std::cout << "Choose an option:\n";
        std::cout << "1. Update version\n";
        std::cout << "2. Update revision\n";
        std::cout << "0. Quit\n";

        int option;
        std::cin >> option;

        if (option == 0)
        {
            std::cout << "Exiting...\n";
            break;
        }
        else if (option == 1 || option == 2)
        {
            std::string version, revision;
            bool versionChanged = false;
            bool revisionChanged = false;
            bool addCommentToPrevDate = false;
            bool addPrevToFileNames = false;

            if (option == 1)
            {
                version = getValidVersionNumber();
                if (version.length() != 3)
                {
                    std::cout << "Version number must be exactly 3 digits.\n";
                    continue;
                }

                std::ifstream logFile("version_change_log.txt");
                std::string line;
                bool versionIncremented = false;
                bool sameVersionUploaded = false;
                while (std::getline(logFile, line))
                {
                    if (line.find("Version: " + version) != std::string::npos)
                    {
                        versionIncremented = true;
                        break;
                    }
                }
                logFile.close();

                if (!versionIncremented)
                {
                    logFile.open("version_change_log.txt");
                    while (std::getline(logFile, line))
                    {
                        if (line.find("Version: ") != std::string::npos)
                        {
                            std::string prevVersion = line.substr(9, 3);
                            if (prevVersion == version)
                            {
                                sameVersionUploaded = true;
                                break;
                            }
                        }
                    }
                    logFile.close();

                    if (!sameVersionUploaded)
                    {
                        revision = "01";
                        versionChanged = true;
                        addCommentToPrevDate = true;
                        addPrevToFileNames = true;
                        std::cout << "Changing version number to " << version << ".\n";

                        logFile.open("version_change_log.txt");
                        std::vector<std::string> logLines;
                        std::string prevVersion;
                        bool prevVersionChanged = false;
                        while (std::getline(logFile, line))
                        {
                            if (line.find("Version: ") != std::string::npos)
                            {
                                prevVersion = line.substr(9, 3);
                                prevVersionChanged = (prevVersion != version);
                            }
                            if (prevVersionChanged && line.find("Updated file: ") != std::string::npos)
                            {
                                if (line.find("_Prev") == std::string::npos)
                                {
                                    if (!line.empty() && line.substr(0, 3) != "// ")
                                    {
                                        line = "// " + line;
                                    }
                                    line += " _Prev";
                                }
                                prevVersionChanged = false;
                            }
                            logLines.push_back(line);
                        }
                        logFile.close();

                        updateLogFile(logLines);

                        std::ofstream outFile("version_change_log.txt", std::ios_base::app);
                        if (!outFile.is_open())
                        {
                            std::cerr << "Error opening log file." << std::endl;
                            return 1;
                        }

                        std::string formattedVersion = std::string(3 - version.length(), '0') + version;
                        std::string logEntry = "Date: " + getCurrentDateTime() + " - Version: " + formattedVersion + " - Revision: " + revision;

                        std::vector<std::string> headerFiles = {"header_1.h", "header_2.h"};
                        for (const std::string &header : headerFiles)
                        {
                            if (versionChanged)
                            {
                                logEntry += " - Updated file: " + header + " " + formattedVersion + "-" + revision;
                            }
                            else if (revisionChanged)
                            {
                                logEntry += " - Updated file: " + header + " " + formattedVersion + "-" + revision;
                            }
                        }

                        outFile << logEntry << "\n\n";
                        outFile.close();
                    }
                    else
                    {
                        std::cout << "Same version number " << version << " has already been uploaded. Please enter a different version number.\n";
                    }
                }
                else
                {
                    std::cout << "Version " << version << " already exists. Increment the version number.\n";
                }
            }
            else if (option == 2)
            {
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

                revisionChanged = true;
                addCommentToPrevDate = true;
                addPrevToFileNames = false;
                std::cout << "Changing revision number to " << revision << ".\n";

                logFile.open("version_change_log.txt");
                std::vector<std::string> logLines;
                while (std::getline(logFile, line))
                {
                    if (line.find("Revision: ") != std::string::npos)
                    {
                        if (!line.empty() && line.substr(0, 3) != "// ")
                        {
                            line = "// " + line;
                        }
                    }
                    logLines.push_back(line);
                }
                logFile.close();

                updateLogFile(logLines);

                std::ofstream outFile("version_change_log.txt", std::ios_base::app);
                if (!outFile.is_open())
                {
                    std::cerr << "Error opening log file." << std::endl;
                    return 1;
                }

                std::string formattedVersion = std::string(3 - version.length(), '0') + version;
                std::string formattedRevision = (revision.length() == 1) ? ("0" + revision) : revision;
                std::string logEntry = "Date: " + getCurrentDateTime() + " - Version: " + formattedVersion + " - Revision: " + formattedRevision;

                std::vector<std::string> headerFiles = {"header_1.h", "header_2.h"};
                for (const std::string &header : headerFiles)
                {
                    if (versionChanged)
                    {
                        logEntry += " - Updated file: " + header + " " + formattedVersion + "-" + formattedRevision;
                    }
                    else if (revisionChanged)
                    {
                        logEntry += " - Updated file: " + header + " " + formattedVersion + "-" + formattedRevision;
                    }
                }

                outFile << logEntry << "\n\n";
                outFile.close();
            }
        }
        else
        {
            std::cout << "Invalid option selected. Please try again.\n";
        }
    }

    return 0;
}
