// Include precompiled header (used in Visual Studio) - this helps improve compilation speed
// �v���R���p�C���ς݃w�b�_���܂ށiVisual Studio �Ŏg�p�j-����ɂ��R���p�C�����x�����サ�܂�

#include "stdafx.h"

// Standard C++ libraries
#include <iostream>  // Input and output stream functions // ���o�̓X�g���[���֐�
#include <fstream>   // File stream functions // �t�@�C���X�g���[���֐�
#include <string>    // String manipulation functions // �����񑀍�֐�
#include <vector>    // Dynamic array container // ���I�z��R���e�i
#include <ctime>     // Date and time functions // ���t�Ǝ����֐�
#include <sstream>   // String stream for string manipulation // �����񑀍�p�̕����X�g���[��
#include <iomanip>   // Input/output manipulators (e.g., setw, setfill) // ���o�͑���q�i��Fsetw�Asetfill�j
#include <algorithm> // Algorithms for manipulating sequences (e.g., std::find) // �V�[�P���X�̑���̂��߂̃A���S���Y���i��Fstd::find�j
#include <chrono>    // Time-related functions // ���Ԋ֘A�̊֐�
#include <regex>     // Regular expressions for pattern matching // �p�^�[���}�b�`���O�̂��߂̐��K�\��

// Define NOMINMAX before including Windows.h to prevent conflicts with min/max macros
// Windows.h ���܂ޑO�� NOMINMAX ���`���āAmin/max �}�N���Ƃ̋�����h��

#define NOMINMAX
#include <Windows.h> // Windows API functions and data types // Windows API �֐��ƃf�[�^�^

// Function to get the current date in "yyyy/mm/dd" format
// "yyyy/mm/dd" �`���Ō��݂̓��t���擾����֐�
std::string getCurrentDate()
{
    std::time_t now = std::time(nullptr);
    char dateBuffer[11]; // 10 characters for "yyyy/mm/dd" plus the null terminator
    struct tm localTime;
    localtime_s(&localTime, &now);
    std::strftime(dateBuffer, sizeof(dateBuffer), "%Y/%m/%d", &localTime);

    return dateBuffer;
}

// ������������擾����֐� // Using for Log File
std::string getDatetimeStr()
{
    time_t t = time(nullptr);

    struct tm localTime;
    if (localtime_s(&localTime, &t) != 0)
    {
        // Handle the error if localtime_s fails
        // For example, you could return an empty string or a default value
        // localtime_s �����s�����ꍇ�̃G���[����
        // �Ⴆ�΁A��̕������f�t�H���g�l��Ԃ����Ƃ��ł��܂�
        return "";
    }

    std::stringstream s;
    s << localTime.tm_year + 1900;
    s << "/" << std::setw(2) << std::setfill('0') << localTime.tm_mon + 1;
    s << "/" << std::setw(2) << std::setfill('0') << localTime.tm_mday;

    return s.str();
}

// Check if a file exists at the given file path
// �w�肵���t�@�C���p�X�Ƀt�@�C�������݂��邩���`�F�b�N����֐�
bool fileExists(const std::string &filePath)
{
    std::ifstream file(filePath);
    return file.good(); // Return whether the file is in good state // �t�@�C��������ȏ�Ԃł��邩��Ԃ�
}

// Find the line containing the main version information in the file
// �t�@�C�����̃��C���o�[�W���������܂ލs��������֐�
std::string findMainVersionLine(const std::vector<std::string> &fileLines)
{
    for (const std::string &line : fileLines)
    {
        // Check if the line contains "const Vi_Version" and is not commented out or marked as "_Prev"
        // �s�� "const Vi_Version" ���܂܂�A�R�����g�A�E�g����Ă��Ȃ��� "_Prev" �Ƃ��ă}�[�N����Ă��Ȃ������m�F
        if (line.find("const Vi_Version") != std::string::npos &&
            line.find("//") != 0 &&
            line.find("_Prev") == std::string::npos)
        {
            return line; // Return the main version line // ���C���o�[�W�����s��Ԃ�
        }
    }
    // Return an empty string if no valid main version line is found
    // �L���ȃ��C���o�[�W�����s��������Ȃ��ꍇ�͋�̕������Ԃ�
    return ""; // Return an empty string if no valid main version line is found
}

// Overloaded function to get the local time in the form of a tm struct
// �^�C���X�^���v���擾����֐��i�I�[�o�[���[�h�Łj
struct tm getLocalTime(const time_t *time)
{
    struct tm localTime;
    localtime_s(&localTime, time);
    return localTime;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

// Function to update the log file with relevant information about changes
// �ύX�Ɋւ���֘A�����܂ރ��O�t�@�C�����X�V����֐�
void updateLogFile(const std::string &logFilePath, const std::string &fileName, const std::string &mainVersionChange, const std::string &revisionChange)
{
    // Open or create the log file in append mode
    // ���O�t�@�C����ǋL���[�h�ŊJ���܂��͍쐬����
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (!logFile)
    {
        // If the file cannot be opened or created, show an error message and return
        // �t�@�C�����J���܂��͍쐬�ł��Ȃ��ꍇ�A�G���[���b�Z�[�W��\�����Ė߂�
        std::cerr << "�G���[ : update_log.txt ���J�����쐬�ł��܂���ł����B" << std::endl;
        return;
    }

    // Get the current local time in "yyyy-mm-dd HH:MM:SS" format
    // ���݂̃��[�J���^�C���� "yyyy-mm-dd HH:MM:SS" �`���Ŏ擾
    std::time_t now = std::time(nullptr);
    struct tm localTime;
    localtime_s(&localTime, &now);

    char currentTimeBuffer[20]; // 19 characters for "yyyy-mm-dd HH:MM:SS" plus the null terminator // "yyyy-mm-dd HH:MM:SS" �ɉ����ăk���I�[�q�̂��߂� 19 ����
    strftime(currentTimeBuffer, sizeof(currentTimeBuffer), "%Y-%m-%d %H:%M:%S", &localTime);
    std::string currentTime = currentTimeBuffer;

    // Write the current local time to the log file
    // ���݂̃��[�J���^�C�������O�t�@�C���ɏ�������
    logFile << currentTime << " ";

    // Write the file name to the log file
    // �t�@�C���������O�t�@�C���ɏ�������
    logFile << fileName << " ";

    // Write the main version change information if it's provided
    // ���C���o�[�W�����̕ύX��񂪒񋟂���Ă���ꍇ�́A���O�t�@�C���ɏ�������
    if (!mainVersionChange.empty())
    {
        logFile << "���C���o�[�W�������ύX����܂��� : " << mainVersionChange << " ";
    }

    // Write the revision change information if it's provided
    // ���r�W�����̕ύX��񂪒񋟂���Ă���ꍇ�́A���O�t�@�C���ɏ�������
    if (!revisionChange.empty())
    {
        logFile << "���r�W�������ύX����܂��� : " << revisionChange << " ";
    }

    // Write a newline character to end the log entry
    // ���s��������������Ń��O�G���g�����I������
    logFile << std::endl;

    // Close the log file
    // ���O�t�@�C�������
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

// ���C���o�[�W�������X�V����֐�
void updateMainVersion(std::vector<std::string> &fileLines, const std::string &filePath, const std::string &fileName)
{
    std::string newVersionLine;

    // Step 1: Find the current main version line in the list of file lines
    // �X�e�b�v 1: �t�@�C���s�̃��X�g���Ō��݂̃��C���o�[�W�����s��������
    std::string currentMainVersionLine = findMainVersionLine(fileLines);
    if (!currentMainVersionLine.empty() && currentMainVersionLine.find("_Prev") == std::string::npos)
    {
        std::cout << "���݂̃��C���o�[�W�����s : " << currentMainVersionLine << std::endl;

        // Extract elements inside ""
        // "" ���̗v�f�𒊏o
        std::vector<std::string> elements;
        size_t startPos = currentMainVersionLine.find("\"");
        size_t endPos = currentMainVersionLine.find("\"", startPos + 1);
        while (startPos != std::string::npos && endPos != std::string::npos)
        {
            // Extract and store elements between quotes
            // ���p���Ԃ̗v�f�𒊏o���Ċi�[
            elements.push_back(currentMainVersionLine.substr(startPos + 1, endPos - startPos - 1));
            startPos = currentMainVersionLine.find("\"", endPos + 1);
            endPos = currentMainVersionLine.find("\"", startPos + 1);
        }

        // Descriptions for each element
        // �e�v�f�̐���
        std::vector<std::string> elementDescriptions(7);
        elementDescriptions[0] = "�v�f : �R���|�[�l���g";
        elementDescriptions[1] = "�v�f : ���t";
        elementDescriptions[2] = "�v�f : ���C���o�[�W����";
        elementDescriptions[3] = "�v�f : ���r�W����";
        elementDescriptions[4] = "�v�f : ���ʎq";
        elementDescriptions[5] = "�v�f : �s��1";
        elementDescriptions[6] = "�v�f : �s��2";

        // Display element descriptions along with their extracted values
        // �v�f�̐����ƒ��o���ꂽ�l��\��
        for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
        {
            std::cout << elementDescriptions[i] << ": " << elements[i] << std::endl;
        }

        // Step 2: Extract the current main version and revision numbers from the main version line
        // �X�e�b�v 2: ���C���o�[�W�����s���猻�݂̃��C���o�[�W�����ƃ��r�W�����ԍ��𒊏o
        std::string mainVersionFromLine;
        std::string revisionFromLine;

        size_t mainVersionPos = currentMainVersionLine.find("\"" + elements[2] + "\"");
        size_t revisionPos = currentMainVersionLine.find("\"" + elements[3] + "\"");

        if (mainVersionPos != std::string::npos)
        {
            mainVersionFromLine = elements[2]; // Save the current main version number // ���݂̃��C���o�[�W�����ԍ���ۑ�
        }
        if (revisionPos != std::string::npos)
        {
            revisionFromLine = elements[3]; // Save the current revision number // ���݂̃��r�W�����ԍ���ۑ�
        }

        // Display the current main version and revision numbers
        // ���݂̃��C���o�[�W�����ƃ��r�W�����ԍ���\��
        std::cout << "���݂̃��C���o�[�W���� : " << mainVersionFromLine << std::endl;
        std::cout << "���݂̃��r�W���� : " << revisionFromLine << std::endl;

        // Step 3: Find the main version number (3 digits) and ensure the revision number is 2 digits
        // �X�e�b�v 3: ���C���o�[�W�����ԍ������o���i3 ���j�A���r�W�����ԍ��� 2 ���ł��邱�Ƃ��m�F
        std::string newMainVersion;
        std::cout << "�V�������C���o�[�W��������͂��Ă�����(3 ��) : ";
        std::getline(std::cin, newMainVersion);

        // Add leading zeros to the new main version number if needed
        // �K�v�ɉ����ĐV�������C���o�[�W�����ԍ��ɐ�s�[����ǉ�
        while (newMainVersion.length() < 3)
        {
            newMainVersion = "0" + newMainVersion;
        }

        std::string newRevision;
        if (newMainVersion.length() == 3 && std::all_of(newMainVersion.begin(), newMainVersion.end(), ::isdigit))
        {
            newRevision = "01"; // Reset revision to '01' // ���r�W������ '01' �Ƀ��Z�b�g
        }
        else
        {
            newRevision = revisionFromLine; // Keep the original revision // �I���W�i���̃��r�W������ێ�
        }

        std::cout << "�V�������C���o�[�W���� : " << newMainVersion << std::endl;
        std::cout << "�V�������r�W���� : " << newRevision << std::endl;

        // Step 4: Extract the identifier prefix from the current main version line
        // �X�e�b�v 4: ���݂̃��C���o�[�W�����s���环�ʎq�̐ړ����𒊏o
        std::string identifierPrefix;
        size_t identifierStartPos = elements[4].find("RELS_");
        if (identifierStartPos != std::string::npos)
        {
            identifierStartPos += sizeof("RELS_") - 1; // Move past "RELS_" to the identifier prefix // "RELS_" �̎��Ɉړ����Ď��ʎq�̐ړ����Ɉړ�
            size_t identifierEndPos = elements[4].find("-", identifierStartPos);
            if (identifierEndPos != std::string::npos)
            {
                identifierPrefix = elements[4].substr(identifierStartPos, identifierEndPos - identifierStartPos) + "_";

                // Print the extracted identifier prefix for debugging
                // �f�o�b�O�p�ɒ��o�������ʎq�̐ړ�����\��
                std::cout << "���o�������ʎq�̐ړ��� : " << identifierPrefix << std::endl;
            }
        }

        // Replace the main version in the identifier with the new main version number
        // ���ʎq���̃��C���o�[�W������V�������C���o�[�W�����ԍ��Œu��������
        std::string modifiedIdentifier = "RELS_" + identifierPrefix + newMainVersion + "-" + newRevision;
        size_t identifierDashPos = modifiedIdentifier.find('-');
        if (identifierDashPos != std::string::npos)
        {
            modifiedIdentifier = modifiedIdentifier.substr(0, identifierDashPos + 1) + newRevision;
        }

        // Construct the new identifier using the extracted components and the new main version
        // ���o�����v�f�ƐV�������C���o�[�W�������g�p���ĐV�������ʎq���\�z
        std::string newIdentifier = elements[4]; // Assuming the Identifier element is at index 4  // ���ʎq�v�f���C���f�b�N�X 4 �ɂ���Ɖ���

        // Find the position of the main version number in the identifier
        // ���ʎq���̃��C���o�[�W�����ԍ��̈ʒu�����o
        size_t mainVersionStartPos = newIdentifier.find_last_of('_') + 1;
        size_t mainVersionEndPos = newIdentifier.find('-', mainVersionStartPos);
        if (mainVersionStartPos != std::string::npos && mainVersionEndPos != std::string::npos)
        {
            // Replace the old main version number with the new one
            // �Â����C���o�[�W�����ԍ���V�������̂Œu��������
            newIdentifier.replace(mainVersionStartPos, mainVersionEndPos - mainVersionStartPos, newMainVersion);
        }

        // Reset the identifier's revision to '01' if main version is 3 digits and all digits
        // ���C���o�[�W������ 3 �������ׂĂ̌��������̏ꍇ�A���r�W������ '01' �Ƀ��Z�b�g
        if (newMainVersion.length() == 3 && std::all_of(newMainVersion.begin(), newMainVersion.end(), ::isdigit))
        {
            size_t revisionStartPos = newIdentifier.find('-', mainVersionEndPos);
            if (revisionStartPos != std::string::npos)
            {
                newIdentifier.replace(revisionStartPos + 1, 2, "01");
            }
        }

        // Add leading zeros to the new main version number if needed
        // �K�v�ɉ����ĐV�������C���o�[�W�����ԍ��ɐ�s�[����ǉ�
        while (newMainVersion.length() < 3)
        {
            newMainVersion = "0" + newMainVersion;
        }

        // Add leading zeros to the new revision number if needed
        // �K�v�ɉ����ĐV�������r�W�����ԍ��ɐ�s�[����ǉ�
        while (newRevision.length() < 2)
        {
            newRevision = "0" + newRevision;
        }

        // �V�����v�f�̐����ƒl��\��
        std::cout << "�V�������C���o�[�W�����F" << newMainVersion << std::endl;
        std::cout << "�V�������r�W�����F" << newRevision << std::endl;

        // �X�e�b�v 5: �V�������C���o�[�W�����s���쐬���A�t�@�C���s�̃��X�g���Ō��݂̃��C���o�[�W�����s��u��������

        // Convert the new main version number to a string with leading zeros
        // �V�������C���o�[�W�����ԍ����s�[�����܂ޕ�����ɕϊ�
        std::stringstream formattedMainVersion;
        formattedMainVersion << std::setw(3) << std::setfill('0') << newMainVersion;

        // Construct the new main version line with updated main version, revision numbers, and modified identifier
        // �X�V���ꂽ���C���o�[�W�����A���r�W�����ԍ��A�C���ςݎ��ʎq���܂ސV�������C���o�[�W�����s���\�z
        std::string currentDate = getCurrentDate();

        // Construct the new main version line with updated main version, revision numbers, and modified identifier
        // �X�V���ꂽ���C���o�[�W�����A���r�W�����ԍ��A�C���ςݎ��ʎq���܂ސV�������C���o�[�W�����s���\�z
        std::string newMainVersionLine = "const Vi_Version " + trim(elements[0]) + "_Version( \"" + trim(elements[0]) + "\", \"" + trim(currentDate) + "\", \"" +
                                         formattedMainVersion.str() + "\", \"" + newRevision + "\", \"" + newIdentifier + "\", \"" +
                                         trim(elements[5]) + "\", \"" + trim(elements[6]) + "\");";

        // Find the position of the current main version line
        // ���݂̃��C���o�[�W�����s�̈ʒu��������
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
        // �V�������C���o�[�W�����s�����݂̃��C���o�[�W�����s�̉��ɑ}��
        fileLines.insert(fileLines.begin() + currentMainVersionPos + 1, newMainVersionLine);

        // Add "//" to lines containing "_Prev" and ".Prev"
        // "_Prev" �� ".Prev" ���܂ލs�� "//" ��ǉ�
        for (std::string &line : fileLines)
        {
            if ((line.find("_Prev") != std::string::npos || line.find(".Prev") != std::string::npos) && line.find("//") != 0)
            {
                line = "//" + line;
            }
        }

        // Add "_Prev" to the current main version line
        // ���݂̃��C���o�[�W�����s�� "_Prev" ��ǉ�
        auto it = std::find(fileLines.begin(), fileLines.end(), currentMainVersionLine);
        if (it != fileLines.end())
        {
            size_t versionPos = it->find("_Version");
            if (versionPos != std::string::npos)
            {
                size_t parenthesisPos = it->find("(", versionPos);
                if (parenthesisPos != std::string::npos)
                {
                    size_t prevPos = it->find("_Prev", versionPos + 8); // Length of "_Version" // "_Version" �̒���
                    if (prevPos != std::string::npos)
                    {
                        // Remove any spaces before "_Prev"
                        // "_Prev" �̑O�̗]���ȃX�y�[�X���폜
                        size_t spacePos = it->rfind(" ", prevPos);
                        if (spacePos != std::string::npos)
                        {
                            it->erase(spacePos, 1);
                        }
                        // Add a space after "_Prev" before the opening parenthesis
                        // "(" �̑O�� "_Prev" �̌��ɃX�y�[�X��ǉ�
                        it->insert(prevPos + 5, " ");
                    }

                    *it = it->substr(0, parenthesisPos) + "_Prev " + it->substr(parenthesisPos); // Added space after "_Prev"

                    // Append ".Prev" to the component name
                    // �R���|�[�l���g���� ".Prev" ��ǉ�
                    size_t componentStartPos = it->find("\"", parenthesisPos);
                    size_t componentEndPos = it->find("\"", componentStartPos + 1);
                    if (componentStartPos != std::string::npos && componentEndPos != std::string::npos)
                    {
                        std::string component = it->substr(componentStartPos + 1, componentEndPos - componentStartPos - 1);
                        component = trim(component);
                        std::string modifiedComponent = component + ".Prev";
                        *it = it->substr(0, componentStartPos + 1) + modifiedComponent + it->substr(componentEndPos);

                        // Remove extra spaces
                        // �]���ȃX�y�[�X���폜
                        size_t pos = it->find("  ");
                        while (pos != std::string::npos)
                        {
                            it->replace(pos, 2, " ");
                            pos = it->find("  ");
                        }

                        // Trim spaces at the beginning and end of the line
                        // �s�̐擪�Ɩ����̃X�y�[�X���g����
                        size_t startPos = it->find_first_not_of(" ");
                        size_t endPos = it->find_last_not_of(" ");
                        if (startPos != std::string::npos && endPos != std::string::npos)
                        {
                            *it = it->substr(startPos, endPos - startPos + 1);
                        }
                    }
                }
            }
        }

        // Update the log file with the changes made
        // �ύX���e�����O�t�@�C���ɍX�V
        std::string directoryPath = filePath.substr(0, filePath.find_last_of("\\/"));
        std::string logMessage = mainVersionFromLine + " -> " + newMainVersion;
        updateLogFile(directoryPath + "\\update_log.txt", fileName, logMessage, "");

        // Display the new main version line
        // �V�������C���o�[�W�����s��\��
        std::cout << "�V�������C���o�[�W�����s�F " << newMainVersionLine << std::endl;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

void updateRevision(std::vector<std::string> &fileLines, const std::string &filePath, const std::string &fileName)
{
    // Extract elements from the main version line
    // ���C���o�[�W�����s����v�f�𒊏o
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
    // �v�f�̐��������[�v���g���ď�����
    std::vector<std::string> elementDescriptions(7);
    // extract first line
    // 1�s�ڂ𒊏o
    elementDescriptions[0] = "�v�f : �R���|�[�l���g";
    elementDescriptions[1] = "�v�f : ���t";
    elementDescriptions[2] = "�v�f : ���C���o�[�W����";
    elementDescriptions[3] = "�v�f : ���r�W����";
    elementDescriptions[4] = "�v�f : ���ʎq";
    elementDescriptions[5] = "�v�f : �s��1";
    elementDescriptions[6] = "�v�f : �s��2";

    std::cout << "���C���o�[�W�����s���璊�o���ꂽ�v�f�F" << std::endl;
    for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
    {
        std::cout << elementDescriptions[i] << ": " << elements[i] << std::endl;
    }

    // Step 4: Extract the revision number
    // �X�e�b�v4�F���r�W�����ԍ��𒊏o
    std::string currentRevision = elements[3]; // Assuming revision is at index 3 // ���r�W�����̓C���f�b�N�X3�Ɖ���

    // Step 5: Increment the revision
    // �X�e�b�v5�F���r�W�����ԍ��𑝂₷
    int incrementedRevision = std::stoi(currentRevision) + 1;
    std::string newRevision = (incrementedRevision < 10) ? "0" + std::to_string(incrementedRevision) : std::to_string(incrementedRevision);

    // Step 6: Create the new line with updated revision number and formatted date
    // �X�e�b�v6�F�X�V���ꂽ���r�W�����ԍ��ƃt�H�[�}�b�g���ꂽ���t�ŐV�����s���쐬
    std::string newRevisionLine = mainVersionLine;
    size_t revisionPos = newRevisionLine.find("\"" + currentRevision + "\"");
    if (revisionPos != std::string::npos)
    {
        newRevisionLine.replace(revisionPos + 1, currentRevision.length(), newRevision);
    }

    // Update the Date element with the new formatted date
    // �V�����s�̓��t�v�f���X�V
    size_t datePos = newRevisionLine.find("\"" + elements[1] + "\"");
    if (datePos != std::string::npos)
    {
        std::string currentDate = getCurrentDate();
        newRevisionLine.replace(datePos + 1, elements[1].length(), currentDate);
    }

    // Get the revision number from the new line
    // �V�����s���烊�r�W�����ԍ����擾
    std::string newLineRevision = newRevision;

    // Update the Identifier element
    // ���ʎq�v�f���X�V
    size_t identifierIndex = 4;                         // ���ʎq�v�f�̃C���f�b�N�X
    std::string identifier = elements[identifierIndex]; // ���ʎq�v�f�̓C���f�b�N�X4�Ɖ���

    // Find the revision number in the Identifier
    // ���ʎq���̃��r�W�����ԍ�������
    size_t dashPos = identifier.rfind('-');
    size_t revisionStartPos = dashPos + 1;
    size_t revisionEndPos = identifier.find("\"", revisionStartPos);
    std::string identifierRevision = identifier.substr(revisionStartPos, revisionEndPos - revisionStartPos);

    // Replace the old revision number in the Identifier with the new one from the new line
    // ���ʎq���̌Â����r�W�����ԍ���V�����s����̂��̂Œu��
    identifier.replace(revisionStartPos, revisionEndPos - revisionStartPos, newLineRevision);

    // Update the Identifier line in newRevisionLine
    // �V����Revision Line���̎��ʎq�s���X�V
    size_t identifierPos = newRevisionLine.find(elements[identifierIndex]);
    if (identifierPos != std::string::npos)
    {
        size_t endPos = identifierPos + elements[identifierIndex].length();
        newRevisionLine.replace(identifierPos, endPos - identifierPos, identifier);
    }

    // Insert the new revision line below the main version line
    // �V�������r�W�����s�����C���o�[�W�����s�̉��ɑ}��
    auto it = std::find(fileLines.begin(), fileLines.end(), mainVersionLine);
    if (it != fileLines.end())
    {
        // Calculate the position to insert the new revision line
        // �V�������r�W�����s��}������ʒu���v�Z
        size_t insertPos = std::distance(fileLines.begin(), it) + 1;

        // Insert the new revision line
        // �V�������r�W�����s��}��
        fileLines.insert(fileLines.begin() + insertPos, newRevisionLine);
    }

    // Step 9: Add comment to the old line
    // �X�e�b�v9�F�Â��s�ɃR�����g��ǉ�
    for (size_t i = 0; i < fileLines.size(); ++i)
    {
        if (fileLines[i].find(mainVersionLine) != std::string::npos)
        {
            fileLines[i] = "//" + fileLines[i]; // Add "//" comment to the old line // �Â��s��"//"�̃R�����g��ǉ�
            break;
        }
    }

    // Update the log file with the changes made
    // �ύX���e�����O�t�@�C���ɍX�V
    std::string logFilePath = filePath.substr(0, filePath.find_last_of("\\/")) + "\\update_log.txt";
    updateLogFile(logFilePath, fileName, "", currentRevision + " -> " + newRevision);

    // Display the updated revision line again after logging
    // ���M���O��ɍēx�X�V���ꂽ���r�W�����s��\��
    std::cout << "�X�V���ꂽ���r�W�����s : " << newRevisionLine << std::endl;

    // Save the updated lines back to the file (as before)
    std::ofstream outputFile(filePath);
    for (const std::string &updatedLine : fileLines)
    {
        outputFile << updatedLine << "\n";
    }
    outputFile.close();

    std::cout << "���r�W�������X�V����܂����B�V�������r�W�����F" << newRevision << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

int main()
{
    // Loop to repeatedly prompt the user for file path and options
    // ���[�U�[�Ƀt�@�C���p�X�܂��̓v���O�������I�����邩�̑I�����J��Ԃ��񎦂��郋�[�v
    while (true)
    {
        // Prompt the user to enter the file path or quit the program
        // ���[�U�[�Ƀt�@�C���p�X����͂����邩�A�v���O�������I�������邩��q�˂�
        std::cout << "�t�@�C���p�X����͂��Ă��������i�܂��� '0' �܂��� 'q' ����͂��ăv���O�������I���j�F";
        std::string filePath;
        std::getline(std::cin, filePath);

        // Check if the user wants to quit the program
        // �v���O�������I�����邩�ǂ������m�F
        if (filePath == "0" || filePath == "q")
        {
            std::cout << "Quitting the program." << std::endl;
            break;
        }

        // Check if the specified file exists
        // �w�肳�ꂽ�t�@�C�������݂��邩���m�F
        if (!fileExists(filePath))
        {
            std::cout << "File not found at the specified path." << std::endl;
            continue; // Skip to the next iteration of the loop
        }

        // Extract the file name from the file path
        std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);

        // Read the contents of the file into a vector of strings (each line as an element)
        // �t�@�C���̓��e��ǂݍ��݁A�e�s��v�f�Ƃ��镶����x�N�^�Ɋi�[

        std::vector<std::string> fileLines;
        std::string line;
        std::ifstream inputFile(filePath);
        while (std::getline(inputFile, line))
        {
            fileLines.push_back(line);
        }
        inputFile.close();

        // Find the main version line in the file
        // �t�@�C�����Ń��C���o�[�W�����s������
        std::string mainVersionLine = findMainVersionLine(fileLines);

        // Check if a valid main version line is found
        // �L���ȃ��C���o�[�W�����s���������������m�F
        if (!mainVersionLine.empty())
        {
            std::cout << "File found: ���p�\�ȃt�@�C���F" << fileName << std::endl;
            std::cout << "[ ���C���o�[�W���� ]���X�V����ɂ� '1' ���A[ ���r�W���� ]���X�V����ɂ� '2' ����͂��Ă��������F";
            int option;
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

            // Check the chosen option
            // �I�����ꂽ�I�v�V�������m�F
            if (option == 1)
            {
                // Call the function to update the main version
                // ���C���o�[�W�������X�V����֐����Ăяo��
                updateMainVersion(fileLines, filePath, fileName);

                // Write the updated lines back to the file
                // �X�V���ꂽ�s���t�@�C���ɏ�������
                std::ofstream outputFile(filePath);
                for (const std::string &updatedLine : fileLines)
                {
                    outputFile << updatedLine << "\n";
                }
                outputFile.close();

                // Update the main version line after the file has been modified
                // �t�@�C�����ύX���ꂽ��Ƀ��C���o�[�W�����s���X�V
                mainVersionLine = findMainVersionLine(fileLines);
            }
            else if (option == 2)
            {
                // Call the function to update the revision
                // ���r�W�������X�V����֐����Ăяo��
                updateRevision(fileLines, filePath, fileName);

                // Write the updated lines back to the file
                // �X�V���ꂽ�s���t�@�C���ɏ�������
                std::ofstream outputFile(filePath);
                for (const std::string &updatedLine : fileLines)
                {
                    outputFile << updatedLine << "\n";
                }
                outputFile.close();
            }

            else
            {
                std::cout << "�����ȃI�v�V�����ł��B'1' �܂��� '2' ��I�����Ă��������B" << std::endl;
            }
        }
        else
        {
            std::cout << "�t�@�C�����ŗL���ȃ��C���o�[�W�����s��������܂���B" << std::endl;
        }

        // Ask the user if they want to continue or quit the program
        // ���[�U�[�ɑ��s���邩�v���O�������I�����邩��q�˂�
        std::cout << "���s���܂����H�i�v���O�������I������ɂ� '0' �܂��� 'q' �������A���s����ɂ͑��̃L�[�������Ă��������j�F";
        std::string quitChoice;
        std::getline(std::cin, quitChoice);

        // Check if the user wants to quit the program
        // �v���O�������I�����邩�ǂ������m�F
        if (quitChoice == "0" || quitChoice == "q")
        {
            std::cout << "Quitting the program. �v���O�������I�����܂��B" << std::endl;
            break;
        }
    } // End of while loop // ���[�v�̏I���

    return 0;
}