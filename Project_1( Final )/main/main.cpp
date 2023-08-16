#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

// Function to generate current date and time
// 現在の日時を生成する関数
std::string getCurrentDateTime()
{
    std::time_t now = std::time(0);                                  // Get current time in seconds since epoch
    std::tm *ltm = std::localtime(&now);                             // Convert to local time structure
    char buffer[20];                                                 // Buffer to hold formatted date and time
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm); // Format date and time as string
    return buffer;                                                   // Return formatted date and time
}

// Function to get valid 3-digit version number from user
// ユーザーから有効な3桁のバージョン番号を取得する関数
std::string getValidVersionNumber()
{
    std::string version;     // Variable to hold the version number
    bool validInput = false; // Flag to track if input is valid

    while (!validInput)
    {
        std::cout << "新しいバージョン番号を入力してくださ(3桁) : ";
        std::cin >> version;

        if (version.length() != 3) // Check if the version number has exactly 3 digits
        {
            std::cout << "バージョン番号は正確に3桁でなければなりません。\n";
        }
        else
        {
            bool allDigits = true;
            for (char c : version) // Iterate through each character in the version number
            {
                if (!std::isdigit(c)) // Check if the character is a digit
                {
                    allDigits = false;
                    break;
                }
            }

            if (allDigits)
            {
                validInput = true; // Set validInput to true if all characters are digits
            }
            else
            {
                std::cout << "バージョン番号は数字のみを含める必要があります。\n";
            }
        }
    }

    return version; // Return the valid version number
}

bool isFirstRun()
{
    std::ifstream logFile("version_change_log.txt"); // Open log file for reading
    return !logFile.good();                          // Return true if the log file is not open or doesn't exist (first run)
}

// Function to update the log file with formatted lines
// ログファイルをフォーマットされた行で更新する関数
void updateLogFile(const std::vector<std::string> &logLines)
{
    std::ofstream outFile("version_change_log.txt"); // Open log file for writing
    for (const std::string &logLine : logLines)      // Iterate through each log line
    {
        outFile << logLine << '\n'; // Write the log line to the file
    }
    outFile.close(); // Close the file
}

int main()
{
    if (isFirstRun()) // Check if it's the first run of the program
    {
        std::ofstream logFile("version_change_log.txt"); // Create or open log file for writing
        if (logFile.is_open())                           // Check if the file is successfully opened
        {
            logFile << "これはバージョン変更とリビジョン変更のためのログシステムです。\n\n"; // Write initial message
            logFile.close();                                                                 // Close the file
        }
        else
        {
            std::cerr << "ログファイルの作成中にエラーが発生しました。\n"
                      << std::endl; // Display error message if file creation fails
            return 1;               // Return an error code
        }
    }

    while (true) // Start an infinite loop for the main program menu
    {
        std::cout << "オプションを選択してください：\n";
        std::cout << "1. バージョンを更新\n";
        std::cout << "2. リビジョンを更新\n";
        std::cout << "0や文字. 終了\n";

        int option;         // Variable to hold the user's menu choice
        std::cin >> option; // Read the user's menu choice

        if (option == 0) // Check if the user wants to quit the program
        {
            std::cout << "終了しています...\n"; // Display exit message
            break;                              // Exit the loop and end the program
        }
        else if (option == 1 || option == 2) // Check if the user selected option 1 or 2
        {
            std::string version, revision; // Variables to hold version and revision numbers
            bool versionChanged = false;   // Flags to track changes
            bool revisionChanged = false;
            bool addCommentToPrevDate = false;
            bool addPrevToFileNames = false;
            if (option == 1) // Check if the user selected option 1 (Update version)
            {
                version = getValidVersionNumber(); // Get a valid version number from the user
                if (version.length() != 3)         // Check if the version number has exactly 3 digits
                {
                    std::cout << "バージョン番号は正確に3桁でなければなりません。\n";
                    continue; // Skip the rest of the loop and start from the beginning
                }

                std::ifstream logFile("version_change_log.txt"); // Open log file for reading
                std::string line;
                bool versionIncremented = false;
                bool sameVersionUploaded = false;
                while (std::getline(logFile, line)) // Read each line from the log file
                {
                    if (line.find("Version: " + version) != std::string::npos) // Check if the version is already present in the log
                    {
                        versionIncremented = true; // Mark that the version is incremented
                        break;                     // Exit the loop
                    }
                }
                logFile.close(); // Close the log file

                if (!versionIncremented) // Check if the version has not been incremented yet
                {
                    logFile.open("version_change_log.txt"); // Reopen the log file for reading
                    while (std::getline(logFile, line))     // Read each line from the log file
                    {
                        if (line.find("Version: ") != std::string::npos) // Check if a line contains the "Version: " string
                        {
                            std::string prevVersion = line.substr(9, 3); // Extract the previous version number
                            if (prevVersion == version)                  // Check if the previous version matches the current version
                            {
                                sameVersionUploaded = true; // Mark that the same version is uploaded
                                break;                      // Exit the loop
                            }
                        }
                    }
                    logFile.close(); // Close the log file

                    if (!sameVersionUploaded) // Check if the same version has not been uploaded yet
                    {
                        revision = "01";             // Set the revision number to "01"
                        versionChanged = true;       // Mark that the version is changed
                        addCommentToPrevDate = true; // Mark that a comment should be added to previous date
                        addPrevToFileNames = true;   // Mark that "_Prev" should be added to file names

                        std::cout << "\nバージョン番号を " << version << " に変更しています。\n\n";

                        logFile.open("version_change_log.txt"); // Reopen the log file for reading
                        std::vector<std::string> logLines;      // Create a vector to store modified log lines
                        std::string prevVersion;                // Variable to store the previous version
                        bool prevVersionChanged = false;        // Variable to track if the previous version is changed
                        while (std::getline(logFile, line))     // Read each line from the log file
                        {

                            if (line.find("Version: ") != std::string::npos) // Check if a line contains the "Version: " string
                            {
                                prevVersion = line.substr(9, 3);               // Extract the previous version number
                                prevVersionChanged = (prevVersion != version); // Check if the previous version is different
                            }
                            if (prevVersionChanged && line.find("Updated file: ") != std::string::npos) // Check if the previous version changed and the line contains "Updated file: "
                            {
                                if (line.find("_Prev") == std::string::npos) // Check if "_Prev" is not already present in the line
                                {
                                    if (!line.empty() && line.substr(0, 3) != "// ") // Check if the line is not empty and doesn't start with "// "
                                    {
                                        line = "// " + line; // Add "// " at the beginning of the line
                                    }
                                    if (line.find("-01") != std::string::npos) // Check if the line contains "-01"
                                    {
                                        line += " _Prev"; // Add "_Prev" to the line
                                    }
                                }
                                prevVersionChanged = false; // Reset the flag
                            }
                            logLines.push_back(line); // Add the modified line to the vector
                        }
                        logFile.close(); // Close the log file

                        updateLogFile(logLines); // Update the log file with the modified log lines

                        std::ofstream outFile("version_change_log.txt", std::ios_base::app); // Open the log file in append mode
                        if (!outFile.is_open())                                              // Check if the file is successfully opened
                        {
                            std::cerr << "ログファイルを開く際にエラーが発生しました。\n"
                                      << std::endl; // Display an error message
                            return 1;               // Return an error code
                        }

                        std::string formattedVersion = std::string(3 - version.length(), '0') + version;                                         // Format the version number
                        std::string logEntry = "Date: " + getCurrentDateTime() + " - Version: " + formattedVersion + " - Revision: " + revision; // Create a log entry

                        std::vector<std::string> headerFiles = {"header_1.h", "header_2.h"}; // List of header files
                        for (const std::string &header : headerFiles)                        // Iterate over header files
                        {
                            if (versionChanged) // Check if version was changed
                            {
                                logEntry += " - Updated file: " + header + " " + formattedVersion + "-" + revision; // Add log entry for updated version
                            }
                            else if (revisionChanged) // Check if revision was changed
                            {
                                logEntry += " - Updated file: " + header + " " + formattedVersion + "-" + revision; // Add log entry for updated revision
                            }
                        }

                        outFile << logEntry << "\n\n"; // Write the log entry to the log file
                        outFile.close();               // Close the log file
                    }
                    else
                    {
                        std::cout << "同じバージョン番号 " << version << " は既にアップロードされています。異なるバージョン番号を入力してください。\n\n";
                    }
                }
                else
                {
                    std::cout << "バージョン " << version << " は既に存在します。バージョン番号を増やしてください。\n";
                }
            }
            else if (option == 2) // Option for updating revision
            {
                std::ifstream logFile("version_change_log.txt");
                int lastRevision = 0;
                int latestVersion = 0;
                std::string line;
                while (std::getline(logFile, line))
                {
                    if (line.find("Revision: ") != std::string::npos) // Check for lines with "Revision:"
                    {
                        std::size_t foundPos = line.find("Revision: ");
                        std::string revisionStr = line.substr(foundPos + 10, 2); // Extract the revision number
                        if (!revisionStr.empty() && std::isdigit(revisionStr[0]) && std::isdigit(revisionStr[1]))
                        {
                            lastRevision = std::stoi(revisionStr); // Convert to integer and store as last revision
                        }
                    }
                    if (line.find("Version: ") != std::string::npos) // Check for lines with "Version:"
                    {
                        std::size_t foundPos = line.find("Version: ");
                        std::string versionStr = line.substr(foundPos + 9, 3); // Extract the version number
                        if (!versionStr.empty() && std::isdigit(versionStr[0]) && std::isdigit(versionStr[1]) && std::isdigit(versionStr[2]))
                        {
                            latestVersion = std::stoi(versionStr); // Convert to integer and store as latest version
                        }
                    }
                }
                logFile.close();

                lastRevision = (lastRevision + 1) % 100;                                                              // Increment the revision and ensure it's within 2 digits
                revision = (lastRevision < 10) ? ("0" + std::to_string(lastRevision)) : std::to_string(lastRevision); // Format the revision number
                version = (latestVersion > 0) ? std::to_string(latestVersion) : "000";                                // Set version based on the latest version or 000 if none

                revisionChanged = true;      // Mark that revision has changed
                addCommentToPrevDate = true; // Add comments to the previous date
                addPrevToFileNames = false;  // Do not add _Prev to file names

                std::cout << "リビジョン番号を " << revision << " に変更しています。\n";

                logFile.open("version_change_log.txt"); // Re-open the log file
                std::vector<std::string> logLines;
                while (std::getline(logFile, line))
                {
                    if (line.find("Revision: ") != std::string::npos) // Check for lines with "Revision:"
                    {
                        if (!line.empty() && line.substr(0, 3) != "// ")
                        {
                            line = "// " + line; // Comment out the revision line
                        }
                    }
                    logLines.push_back(line); // Add the line to the logLines vector
                }
                logFile.close();

                updateLogFile(logLines); // Update the log file with the modified log lines

                std::ofstream outFile("version_change_log.txt", std::ios_base::app); // Open the log file in append mode
                if (!outFile.is_open())                                              // Check if the file is successfully opened
                {
                    std::cerr << "ログファイルを開く際にエラーが発生しました。\n"
                              << std::endl; // Display an error message
                    return 1;               // Return an error code
                }

                std::string formattedVersion = std::string(3 - version.length(), '0') + version;                                                  // Format the version number
                std::string formattedRevision = (revision.length() == 1) ? ("0" + revision) : revision;                                           // Format the revision number
                std::string logEntry = "Date: " + getCurrentDateTime() + " - Version: " + formattedVersion + " - Revision: " + formattedRevision; // Create a log entry

                std::vector<std::string> headerFiles = {"header_1.h", "header_2.h"}; // List of header files
                for (const std::string &header : headerFiles)                        // Iterate over header files
                {
                    if (versionChanged) // Check if version was changed
                    {
                        logEntry += " - Updated file: " + header + " " + formattedVersion + "-" + formattedRevision; // Add log entry for updated version
                    }
                    else if (revisionChanged) // Check if revision was changed
                    {
                        logEntry += " - Updated file: " + header + " " + formattedVersion + "-" + formattedRevision; // Add log entry for updated revision
                    }
                }

                outFile << logEntry << "\n\n"; // Write the log entry to the log file
                outFile.close();               // Close the log file
            }
        }
        else
        {
            std::cout << "\n無効なオプションが選択されました。もう一度選択してください。\n\n";
        }
    }

    return 0; // Return 0 to indicate successful execution
}