#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

std::string getCurrentDateTime()
{
	std::tm ltm;
	std::time_t now = std::time(0);
	localtime_s(&ltm, &now);
	char buffer[20];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &ltm);
	return buffer;

}

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

void updateFileWithLines(const std::string &filePath, const std::vector<std::string> &lines)
{
    std::ofstream outFile(filePath);
    for (const std::string &line : lines)
    {
        outFile << line << '\n';
    }
    outFile.close();
}

std::vector<std::string> readLinesFromFile(const std::string &filePath)
{
    std::ifstream inFile(filePath);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close();
    return lines;
}

int main()
{
std::vector<std::string> headerFiles;
	headerFiles.push_back("DasAppDCIMVersionInfo");
	headerFiles.push_back("DasEventFilterVersionInfo");
	headerFiles.push_back("DasExdpLoadDataVersionInfo");
	headerFiles.push_back("DasExportParametersVersionInfo");
	headerFiles.push_back("DasExportSEMIObjectsVersionInfo");
	headerFiles.push_back("DasGetEqpTypeVersionInfo");
	headerFiles.push_back("DasMaskApplyVersionInfo");
	headerFiles.push_back("DasUipLoadDataVersionInfo");


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

            if (option == 1)
            {
                version = getValidVersionNumber();
                if (version.length() != 3)
                {
                    std::cout << "Version number must be exactly 3 digits.\n";
                    continue;
                }

                for (const std::string &header : headerFiles)
                {
                    std::string filePath = "..\\Header Files\\" + header + ".h"; // Update the path
                    std::vector<std::string> lines = readLinesFromFile(filePath);

                    for (std::string &line : lines)
                    {
                        if (line.find("Version: ") != std::string::npos)
                        {
                            line = "Version: " + version;
                            versionChanged = true;
                        }
                    }

                    updateFileWithLines(filePath, lines);
                }
            }
            else if (option == 2)
            {
                revision = "01"; // Assuming revision starts from "01"

                for (const std::string &header : headerFiles)
                {
                    std::string filePath = "..\\Header Files\\" + header + ".h"; // Update the path
                    std::vector<std::string> lines = readLinesFromFile(filePath);

                    for (std::string &line : lines)
                    {
                        if (line.find("Revision: ") != std::string::npos)
                        {
                            line = "Revision: " + revision;
                            revisionChanged = true;
                        }
                    }

                    updateFileWithLines(filePath, lines);
                }
            }

            if (versionChanged || revisionChanged)
            {
                std::ofstream logFile("version_change_log.txt", std::ios_base::app);
                if (logFile.is_open())
                {
                    logFile << "Date: " << getCurrentDateTime() << " - ";
                    if (versionChanged)
                    {
                        logFile << "Version changed to " << version << " - ";
                    }
                    if (revisionChanged)
                    {
                        logFile << "Revision changed to " << revision << " - ";
                    }
                    logFile << "Updated files: ";
                    for (int i = 0; i < headerFiles.size(); ++i)
                    {
                        logFile << headerFiles[i];
                        if (i < headerFiles.size() - 1)
                        {
                            logFile << ", ";
                        }
                    }
                    logFile << "\n\n";
                    logFile.close();
                }
                else
                {
                    std::cerr << "Error opening log file." << std::endl;
                    return 1;
                }
            }
            else
            {
                std::cout << "No changes made.\n";
            }
        }
        else
        {
            std::cout << "Invalid option selected. Please try again.\n";
        }
    }

    return 0;
}
