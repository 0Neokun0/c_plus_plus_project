#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
#include <algorithm>
#include <sstream>

// Class to represent a version with associated details
class Vi_Version
{
public:
    // Constructor to initialize the version details
    Vi_Version(const std::string &name, const std::string &date, const std::string &num1, const std::string &num2, const std::string &desc, const std::string &empty, const std::string &code)
        : name(name), date(date), num1(num1), num2(num2), desc(desc), empty(empty), code(code) {}

    // Properties for version numbers
    std::string num1;
    std::string num2;

    // Method to print the version details
    void print() const
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "Number 1: " << num1 << std::endl;
        std::cout << "Number 2: " << num2 << std::endl;
        std::cout << "Description: " << desc << std::endl;
        std::cout << "Empty: " << empty << std::endl;
        std::cout << "Code: " << code << std::endl;
    }

    // Method to update the version numbers
    void updateVersion(const std::string &newNum1, const std::string &newNum2)
    {
        num1 = newNum1;
        num2 = newNum2;
        logChange(); // Log the version change
    }

private:
    // Method to log the version change
    void logChange()
    {
        // Open the log file for appending
        std::ofstream logFile("version_change_log.txt", std::ios_base::app);
        if (logFile.is_open())
        {
            // Log the version details in the log file
            logFile << "const Vi_Version " << name << "       (\"" << name << "\", \"" << date << "\", \"" << num1 << "\", \"" << num2 << "\", \"" << desc << "\", \"" << empty << "\", \"" << code << "\");" << std::endl;
            logFile.close();
        }
        else
        {
            std::cerr << "Unable to open log file." << std::endl;
        }
    }

    // Other version details
    std::string name;
    std::string date;
    std::string desc;
    std::string empty;
    std::string code;
};

// Function to get the current sub-version from the log file
std::string getCurrentSubVersion()
{
    // Open the log file for reading
    std::ifstream logFile("version_change_log.txt");
    if (logFile.is_open())
    {
        std::string line;
        while (std::getline(logFile, line))
        {
            // Search for the line containing the version information
            if (line.find("DasAppDCIM_Version       (\"DasAppDCIM\", \"2023/08/15\", \"") != std::string::npos)
            {
                // Extract the current sub-version from the line
                std::size_t pos = line.find("RELS_DASAPPDCIM_") + 16;
                std::string subVersionStr = line.substr(pos, 2);
                logFile.close();
                return subVersionStr;
            }
        }
        logFile.close();
    }
    return "00"; // Default sub-version if not found
}

// Function to update the sub-version in the log file
void updateSubVersionInLog(const std::string &newSubVersion)
{
    // Open the log file for reading and writing
    std::ifstream inputFile("version_change_log.txt");
    std::vector<std::string> lines;

    if (inputFile.is_open())
    {
        std::string line;
        while (std::getline(inputFile, line))
        {
            // Search for the line containing the version information
            if (line.find("DasAppDCIM_Version       (\"DasAppDCIM\", \"2023/08/15\", \"") != std::string::npos)
            {
                // Replace the current sub-version with the new sub-version
                std::size_t pos = line.find("RELS_DASAPPDCIM_") + 16;
                line.replace(pos, 2, newSubVersion);
            }
            lines.push_back(line);
        }
        inputFile.close();

        // Open the log file for writing and update the content
        std::ofstream outputFile("version_change_log.txt");
        if (outputFile.is_open())
        {
            for (const std::string &modifiedLine : lines)
            {
                outputFile << modifiedLine << std::endl;
            }
            outputFile.close();
        }
        else
        {
            std::cerr << "Unable to open log file for writing." << std::endl;
        }
    }
    else
    {
        std::cerr << "Unable to open log file for reading." << std::endl;
    }
}

// Function to comment out a specific line in the log file
void commentOutLogLine(const std::string &lineToComment)
{
    // Open the log file for reading and writing
    std::ifstream inputFile("version_change_log.txt");
    std::vector<std::string> lines;

    if (inputFile.is_open())
    {
        std::string line;
        while (std::getline(inputFile, line))
        {
            // Comment out the specified line and its corresponding _Prev line
            if (line == lineToComment)
            {
                lines.push_back("// " + line);
                std::size_t pos = line.find("Version") + 8;
                lines.push_back("// " + line.substr(0, pos) + "_Prev" + line.substr(pos));
            }
            else
            {
                lines.push_back(line);
            }
        }
        inputFile.close();

        // Open the log file for writing and update the content
        std::ofstream outputFile("version_change_log.txt");
        if (outputFile.is_open())
        {
            for (const std::string &modifiedLine : lines)
            {
                outputFile << modifiedLine << std::endl;
            }
            outputFile.close();
        }
        else
        {
            std::cerr << "Unable to open log file for writing." << std::endl;
        }
    }
    else
    {
        std::cerr << "Unable to open log file for reading." << std::endl;
    }
}

int main()
{
    // Create instances of version objects
    Vi_Version DasAppDCIM_Version_Prev("DasAppDCIM", "2023/08/13", "456", "01", "RELS_DASAPPDCIM_456-01", "", "dxc");
    Vi_Version DasAppDCIM_Version("DasAppDCIM", "2023/08/15", "567", "02", "RELS_DASAPPDCIM_567-02", "", "dxc");

    // Display menu options
    std::cout << "Select an option:\n";
    std::cout << "1. Change version number\n";
    std::cout << "2. Increment sub-version number\n";

    int option;
    std::string newNum1, newNum2;

    while (true)
    {
        // Get user input for the selected option
        std::cin >> option;

        // Option 1: Change version number
        if (option == 1)
        {
            while (true)
            {
                // Prompt user for a new version number
                std::cout << "Enter new version number for DasAppDCIM_Version (3 digits): ";
                std::cin >> newNum1;

                // Validate user input
                bool validInput = true;
                if (newNum1.length() != 3)
                {
                    validInput = false;
                }
                else
                {
                    for (char c : newNum1)
                    {
                        if (!isdigit(c))
                        {
                            validInput = false;
                            break;
                        }
                    }
                }

                // If input is valid, break the loop; otherwise, ask for input again
                if (validInput)
                {
                    break;
                }
                else
                {
                    std::cout << "Invalid input. Please enter a 3-digit number." << std::endl;
                }
            }

            // Check if the new version number is different from the previous one
            if (newNum1 != DasAppDCIM_Version_Prev.num1)
            {
                // Update version and log, and comment out previous log lines
                DasAppDCIM_Version.updateVersion(newNum1, DasAppDCIM_Version_Prev.num2);
                commentOutLogLine("const Vi_Version DasAppDCIM_Version       (\"DasAppDCIM\", \"2023/08/15\", \"" + newNum1 + "\", \"" + DasAppDCIM_Version_Prev.num2 + "\", \"RELS_DASAPPDCIM_" + newNum1 + "-" + DasAppDCIM_Version_Prev.num2 + "\", \"\", \"dxc\");");
                commentOutLogLine("const Vi_Version DasAppDCIM_Version_Prev  (\"DasAppDCIM\", \"2023/08/13\", \"" + DasAppDCIM_Version_Prev.num1 + "\", \"" + DasAppDCIM_Version_Prev.num2 + "\", \"RELS_DASAPPDCIM_" + DasAppDCIM_Version_Prev.num1 + "-" + DasAppDCIM_Version_Prev.num2 + "\", \"\", \"dxc\");");
            }
            else
            {
                // Update version and log, and comment out previous log line
                DasAppDCIM_Version.updateVersion(newNum1, DasAppDCIM_Version_Prev.num2);
                commentOutLogLine("const Vi_Version DasAppDCIM_Version       (\"DasAppDCIM\", \"2023/08/15\", \"" + newNum1 + "\", \"" + DasAppDCIM_Version_Prev.num2 + "\", \"RELS_DASAPPDCIM_" + newNum1 + "-" + DasAppDCIM_Version_Prev.num2 + "\", \"\", \"dxc\");");
            }

            std::cout << "\nUpdated DasAppDCIM_Version:\n";
            DasAppDCIM_Version.print();

            break;
        }
        // Option 2: Increment sub-version number
        else if (option == 2)
        {
            // Get the current sub-version from the log file and increment it
            std::string currentSubVersion = getCurrentSubVersion();
            int subVersion = std::stoi(currentSubVersion);
            subVersion++;

            // Format the new sub-version
            if (subVersion < 10)
            {
                newNum2 = "0" + std::to_string(subVersion);
            }
            else
            {
                newNum2 = std::to_string(subVersion);
            }

            // Update the sub-version in the log file and comment out previous log line
            updateSubVersionInLog(newNum2);
            commentOutLogLine("const Vi_Version DasAppDCIM_Version       (\"DasAppDCIM\", \"2023/08/15\", \"" + DasAppDCIM_Version.num1 + "\", \"" + newNum2 + "\", \"RELS_DASAPPDCIM_" + DasAppDCIM_Version.num1 + "-" + newNum2 + "\", \"\", \"dxc\");");

            // Update the version object and log line
            DasAppDCIM_Version.updateVersion(DasAppDCIM_Version_Prev.num1, newNum2);
            commentOutLogLine("const Vi_Version DasAppDCIM_Version       (\"DasAppDCIM\", \"2023/08/15\", \"" + DasAppDCIM_Version.num1 + "\", \"" + newNum2 + "\", \"RELS_DASAPPDCIM_" + DasAppDCIM_Version.num1 + "-" + newNum2 + "\", \"\", \"dxc\");");

            std::cout << "\nIncremented sub-version. Updated DasAppDCIM_Version:\n";
            DasAppDCIM_Version.print();

            break;
        }
        // Option 3: Comment out log lines
        // else if (option == 3)
        // {
        //     std::cout << "Enter the line to comment out: ";
        //     std::string lineToComment;
        //     std::cin.ignore(); // Clear newline from previous input
        //     std::getline(std::cin, lineToComment);

        //     // Comment out the specified log line and its corresponding _Prev line
        //     commentOutLogLine(lineToComment);
        //     commentOutLogLine(lineToComment + "_Prev");
        //     std::cout << "Log lines commented out." << std::endl;
        // }
        // Invalid option
        else
        {
            std::cout << "Invalid option. Please select either 1 or 2." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}
