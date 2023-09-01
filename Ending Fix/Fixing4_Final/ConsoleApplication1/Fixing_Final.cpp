// Include precompiled header (used in Visual Studio) - this helps improve compilation speed
// プリコンパイル済みヘッダを含む（Visual Studio で使用）-これによりコンパイル速度が向上します

#include "stdafx.h"

// Standard C++ libraries
#include <iostream>  // Input and output stream functions // 入出力ストリーム関数
#include <fstream>   // File stream functions // ファイルストリーム関数
#include <string>    // String manipulation functions // 文字列操作関数
#include <vector>    // Dynamic array container // 動的配列コンテナ
#include <ctime>     // Date and time functions // 日付と時刻関数
#include <sstream>   // String stream for string manipulation // 文字列操作用の文字ストリーム
#include <iomanip>   // Input/output manipulators (e.g., setw, setfill) // 入出力操作子（例：setw、setfill）
#include <algorithm> // Algorithms for manipulating sequences (e.g., std::find) // シーケンスの操作のためのアルゴリズム（例：std::find）
#include <chrono>    // Time-related functions // 時間関連の関数
#include <regex>     // Regular expressions for pattern matching // パターンマッチングのための正規表現

// Define NOMINMAX before including Windows.h to prevent conflicts with min/max macros
// Windows.h を含む前に NOMINMAX を定義して、min/max マクロとの競合を防ぐ

#define NOMINMAX
#include <Windows.h> // Windows API functions and data types // Windows API 関数とデータ型

// Function to get the current date in "yyyy/mm/dd" format
// "yyyy/mm/dd" 形式で現在の日付を取得する関数
std::string getCurrentDate()
{
    std::time_t now = std::time(nullptr);
    char dateBuffer[11]; // 10 characters for "yyyy/mm/dd" plus the null terminator
    struct tm localTime;
    localtime_s(&localTime, &now);
    std::strftime(dateBuffer, sizeof(dateBuffer), "%Y/%m/%d", &localTime);

    return dateBuffer;
}

// 日時文字列を取得する関数 // Using for Log File
std::string getDatetimeStr()
{
    time_t t = time(nullptr);

    struct tm localTime;
    if (localtime_s(&localTime, &t) != 0)
    {
        // Handle the error if localtime_s fails
        // For example, you could return an empty string or a default value
        // localtime_s が失敗した場合のエラー処理
        // 例えば、空の文字列やデフォルト値を返すことができます
        return "";
    }

    std::stringstream s;
    s << localTime.tm_year + 1900;
    s << "/" << std::setw(2) << std::setfill('0') << localTime.tm_mon + 1;
    s << "/" << std::setw(2) << std::setfill('0') << localTime.tm_mday;

    return s.str();
}

// Check if a file exists at the given file path
// 指定したファイルパスにファイルが存在するかをチェックする関数
bool fileExists(const std::string &filePath)
{
    std::ifstream file(filePath);
    return file.good(); // Return whether the file is in good state // ファイルが正常な状態であるかを返す
}

// Find the line containing the main version information in the file
// ファイル内のメインバージョン情報を含む行を見つける関数
std::string findMainVersionLine(const std::vector<std::string> &fileLines)
{
    for (const std::string &line : fileLines)
    {
        // Check if the line contains "const Vi_Version" and is not commented out or marked as "_Prev"
        // 行に "const Vi_Version" が含まれ、コメントアウトされていないか "_Prev" としてマークされていないかを確認
        if (line.find("const Vi_Version") != std::string::npos &&
            line.find("//") != 0 &&
            line.find("_Prev") == std::string::npos)
        {
            return line; // Return the main version line // メインバージョン行を返す
        }
    }
    // Return an empty string if no valid main version line is found
    // 有効なメインバージョン行が見つからない場合は空の文字列を返す
    return ""; // Return an empty string if no valid main version line is found
}

// Overloaded function to get the local time in the form of a tm struct
// タイムスタンプを取得する関数（オーバーロード版）
struct tm getLocalTime(const time_t *time)
{
    struct tm localTime;
    localtime_s(&localTime, time);
    return localTime;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

// Function to update the log file with relevant information about changes
// 変更に関する関連情報を含むログファイルを更新する関数
void updateLogFile(const std::string &logFilePath, const std::string &fileName, const std::string &mainVersionChange, const std::string &revisionChange)
{
    // Open or create the log file in append mode
    // ログファイルを追記モードで開くまたは作成する
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (!logFile)
    {
        // If the file cannot be opened or created, show an error message and return
        // ファイルを開くまたは作成できない場合、エラーメッセージを表示して戻る
        std::cerr << "エラー : update_log.txt を開くか作成できませんでした。" << std::endl;
        return;
    }

    // Get the current local time in "yyyy-mm-dd HH:MM:SS" format
    // 現在のローカルタイムを "yyyy-mm-dd HH:MM:SS" 形式で取得
    std::time_t now = std::time(nullptr);
    struct tm localTime;
    localtime_s(&localTime, &now);

    char currentTimeBuffer[20]; // 19 characters for "yyyy-mm-dd HH:MM:SS" plus the null terminator // "yyyy-mm-dd HH:MM:SS" に加えてヌル終端子のための 19 文字
    strftime(currentTimeBuffer, sizeof(currentTimeBuffer), "%Y-%m-%d %H:%M:%S", &localTime);
    std::string currentTime = currentTimeBuffer;

    // Write the current local time to the log file
    // 現在のローカルタイムをログファイルに書き込む
    logFile << currentTime << " ";

    // Write the file name to the log file
    // ファイル名をログファイルに書き込む
    logFile << fileName << " ";

    // Write the main version change information if it's provided
    // メインバージョンの変更情報が提供されている場合は、ログファイルに書き込む
    if (!mainVersionChange.empty())
    {
        logFile << "メインバージョンが変更されました : " << mainVersionChange << " ";
    }

    // Write the revision change information if it's provided
    // リビジョンの変更情報が提供されている場合は、ログファイルに書き込む
    if (!revisionChange.empty())
    {
        logFile << "リビジョンが変更されました : " << revisionChange << " ";
    }

    // Write a newline character to end the log entry
    // 改行文字を書き込んでログエントリを終了する
    logFile << std::endl;

    // Close the log file
    // ログファイルを閉じる
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

// メインバージョンを更新する関数
void updateMainVersion(std::vector<std::string> &fileLines, const std::string &filePath, const std::string &fileName)
{
    std::string newVersionLine;

    // Step 1: Find the current main version line in the list of file lines
    // ステップ 1: ファイル行のリスト内で現在のメインバージョン行を見つける
    std::string currentMainVersionLine = findMainVersionLine(fileLines);
    if (!currentMainVersionLine.empty() && currentMainVersionLine.find("_Prev") == std::string::npos)
    {
        std::cout << "現在のメインバージョン行 : " << currentMainVersionLine << std::endl;

        // Extract elements inside ""
        // "" 内の要素を抽出
        std::vector<std::string> elements;
        size_t startPos = currentMainVersionLine.find("\"");
        size_t endPos = currentMainVersionLine.find("\"", startPos + 1);
        while (startPos != std::string::npos && endPos != std::string::npos)
        {
            // Extract and store elements between quotes
            // 引用符間の要素を抽出して格納
            elements.push_back(currentMainVersionLine.substr(startPos + 1, endPos - startPos - 1));
            startPos = currentMainVersionLine.find("\"", endPos + 1);
            endPos = currentMainVersionLine.find("\"", startPos + 1);
        }

        // Descriptions for each element
        // 各要素の説明
        std::vector<std::string> elementDescriptions(7);
        elementDescriptions[0] = "要素 : コンポーネント";
        elementDescriptions[1] = "要素 : 日付";
        elementDescriptions[2] = "要素 : メインバージョン";
        elementDescriptions[3] = "要素 : リビジョン";
        elementDescriptions[4] = "要素 : 識別子";
        elementDescriptions[5] = "要素 : 不明1";
        elementDescriptions[6] = "要素 : 不明2";

        // Display element descriptions along with their extracted values
        // 要素の説明と抽出された値を表示
        for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
        {
            std::cout << elementDescriptions[i] << ": " << elements[i] << std::endl;
        }

        // Step 2: Extract the current main version and revision numbers from the main version line
        // ステップ 2: メインバージョン行から現在のメインバージョンとリビジョン番号を抽出
        std::string mainVersionFromLine;
        std::string revisionFromLine;

        size_t mainVersionPos = currentMainVersionLine.find("\"" + elements[2] + "\"");
        size_t revisionPos = currentMainVersionLine.find("\"" + elements[3] + "\"");

        if (mainVersionPos != std::string::npos)
        {
            mainVersionFromLine = elements[2]; // Save the current main version number // 現在のメインバージョン番号を保存
        }
        if (revisionPos != std::string::npos)
        {
            revisionFromLine = elements[3]; // Save the current revision number // 現在のリビジョン番号を保存
        }

        // Display the current main version and revision numbers
        // 現在のメインバージョンとリビジョン番号を表示
        std::cout << "現在のメインバージョン : " << mainVersionFromLine << std::endl;
        std::cout << "現在のリビジョン : " << revisionFromLine << std::endl;

        // Step 3: Find the main version number (3 digits) and ensure the revision number is 2 digits
        // ステップ 3: メインバージョン番号を検出し（3 桁）、リビジョン番号が 2 桁であることを確認
        std::string newMainVersion;
        std::cout << "新しいメインバージョンを入力してくださ(3 桁) : ";
        std::getline(std::cin, newMainVersion);

        // Add leading zeros to the new main version number if needed
        // 必要に応じて新しいメインバージョン番号に先行ゼロを追加
        while (newMainVersion.length() < 3)
        {
            newMainVersion = "0" + newMainVersion;
        }

        std::string newRevision;
        if (newMainVersion.length() == 3 && std::all_of(newMainVersion.begin(), newMainVersion.end(), ::isdigit))
        {
            newRevision = "01"; // Reset revision to '01' // リビジョンを '01' にリセット
        }
        else
        {
            newRevision = revisionFromLine; // Keep the original revision // オリジナルのリビジョンを保持
        }

        std::cout << "新しいメインバージョン : " << newMainVersion << std::endl;
        std::cout << "新しいリビジョン : " << newRevision << std::endl;

        // Step 4: Extract the identifier prefix from the current main version line
        // ステップ 4: 現在のメインバージョン行から識別子の接頭辞を抽出
        std::string identifierPrefix;
        size_t identifierStartPos = elements[4].find("RELS_");
        if (identifierStartPos != std::string::npos)
        {
            identifierStartPos += sizeof("RELS_") - 1; // Move past "RELS_" to the identifier prefix // "RELS_" の次に移動して識別子の接頭辞に移動
            size_t identifierEndPos = elements[4].find("-", identifierStartPos);
            if (identifierEndPos != std::string::npos)
            {
                identifierPrefix = elements[4].substr(identifierStartPos, identifierEndPos - identifierStartPos) + "_";

                // Print the extracted identifier prefix for debugging
                // デバッグ用に抽出した識別子の接頭辞を表示
                std::cout << "抽出した識別子の接頭辞 : " << identifierPrefix << std::endl;
            }
        }

        // Replace the main version in the identifier with the new main version number
        // 識別子内のメインバージョンを新しいメインバージョン番号で置き換える
        std::string modifiedIdentifier = "RELS_" + identifierPrefix + newMainVersion + "-" + newRevision;
        size_t identifierDashPos = modifiedIdentifier.find('-');
        if (identifierDashPos != std::string::npos)
        {
            modifiedIdentifier = modifiedIdentifier.substr(0, identifierDashPos + 1) + newRevision;
        }

        // Construct the new identifier using the extracted components and the new main version
        // 抽出した要素と新しいメインバージョンを使用して新しい識別子を構築
        std::string newIdentifier = elements[4]; // Assuming the Identifier element is at index 4  // 識別子要素がインデックス 4 にあると仮定

        // Find the position of the main version number in the identifier
        // 識別子内のメインバージョン番号の位置を検出
        size_t mainVersionStartPos = newIdentifier.find_last_of('_') + 1;
        size_t mainVersionEndPos = newIdentifier.find('-', mainVersionStartPos);
        if (mainVersionStartPos != std::string::npos && mainVersionEndPos != std::string::npos)
        {
            // Replace the old main version number with the new one
            // 古いメインバージョン番号を新しいもので置き換える
            newIdentifier.replace(mainVersionStartPos, mainVersionEndPos - mainVersionStartPos, newMainVersion);
        }

        // Reset the identifier's revision to '01' if main version is 3 digits and all digits
        // メインバージョンが 3 桁かつすべての桁が数字の場合、リビジョンを '01' にリセット
        if (newMainVersion.length() == 3 && std::all_of(newMainVersion.begin(), newMainVersion.end(), ::isdigit))
        {
            size_t revisionStartPos = newIdentifier.find('-', mainVersionEndPos);
            if (revisionStartPos != std::string::npos)
            {
                newIdentifier.replace(revisionStartPos + 1, 2, "01");
            }
        }

        // Add leading zeros to the new main version number if needed
        // 必要に応じて新しいメインバージョン番号に先行ゼロを追加
        while (newMainVersion.length() < 3)
        {
            newMainVersion = "0" + newMainVersion;
        }

        // Add leading zeros to the new revision number if needed
        // 必要に応じて新しいリビジョン番号に先行ゼロを追加
        while (newRevision.length() < 2)
        {
            newRevision = "0" + newRevision;
        }

        // 新しい要素の説明と値を表示
        std::cout << "新しいメインバージョン：" << newMainVersion << std::endl;
        std::cout << "新しいリビジョン：" << newRevision << std::endl;

        // ステップ 5: 新しいメインバージョン行を作成し、ファイル行のリスト内で現在のメインバージョン行を置き換える

        // Convert the new main version number to a string with leading zeros
        // 新しいメインバージョン番号を先行ゼロを含む文字列に変換
        std::stringstream formattedMainVersion;
        formattedMainVersion << std::setw(3) << std::setfill('0') << newMainVersion;

        // Construct the new main version line with updated main version, revision numbers, and modified identifier
        // 更新されたメインバージョン、リビジョン番号、修正済み識別子を含む新しいメインバージョン行を構築
        std::string currentDate = getCurrentDate();

        // Construct the new main version line with updated main version, revision numbers, and modified identifier
        // 更新されたメインバージョン、リビジョン番号、修正済み識別子を含む新しいメインバージョン行を構築
        std::string newMainVersionLine = "const Vi_Version " + trim(elements[0]) + "_Version( \"" + trim(elements[0]) + "\", \"" + trim(currentDate) + "\", \"" +
                                         formattedMainVersion.str() + "\", \"" + newRevision + "\", \"" + newIdentifier + "\", \"" +
                                         trim(elements[5]) + "\", \"" + trim(elements[6]) + "\");";

        // Find the position of the current main version line
        // 現在のメインバージョン行の位置を見つける
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
        // 新しいメインバージョン行を現在のメインバージョン行の下に挿入
        fileLines.insert(fileLines.begin() + currentMainVersionPos + 1, newMainVersionLine);

        // Add "//" to lines containing "_Prev" and ".Prev"
        // "_Prev" と ".Prev" を含む行に "//" を追加
        for (std::string &line : fileLines)
        {
            if ((line.find("_Prev") != std::string::npos || line.find(".Prev") != std::string::npos) && line.find("//") != 0)
            {
                line = "//" + line;
            }
        }

        // Add "_Prev" to the current main version line
        // 現在のメインバージョン行に "_Prev" を追加
        auto it = std::find(fileLines.begin(), fileLines.end(), currentMainVersionLine);
        if (it != fileLines.end())
        {
            size_t versionPos = it->find("_Version");
            if (versionPos != std::string::npos)
            {
                size_t parenthesisPos = it->find("(", versionPos);
                if (parenthesisPos != std::string::npos)
                {
                    size_t prevPos = it->find("_Prev", versionPos + 8); // Length of "_Version" // "_Version" の長さ
                    if (prevPos != std::string::npos)
                    {
                        // Remove any spaces before "_Prev"
                        // "_Prev" の前の余分なスペースを削除
                        size_t spacePos = it->rfind(" ", prevPos);
                        if (spacePos != std::string::npos)
                        {
                            it->erase(spacePos, 1);
                        }
                        // Add a space after "_Prev" before the opening parenthesis
                        // "(" の前に "_Prev" の後ろにスペースを追加
                        it->insert(prevPos + 5, " ");
                    }

                    *it = it->substr(0, parenthesisPos) + "_Prev " + it->substr(parenthesisPos); // Added space after "_Prev"

                    // Append ".Prev" to the component name
                    // コンポーネント名に ".Prev" を追加
                    size_t componentStartPos = it->find("\"", parenthesisPos);
                    size_t componentEndPos = it->find("\"", componentStartPos + 1);
                    if (componentStartPos != std::string::npos && componentEndPos != std::string::npos)
                    {
                        std::string component = it->substr(componentStartPos + 1, componentEndPos - componentStartPos - 1);
                        component = trim(component);
                        std::string modifiedComponent = component + ".Prev";
                        *it = it->substr(0, componentStartPos + 1) + modifiedComponent + it->substr(componentEndPos);

                        // Remove extra spaces
                        // 余分なスペースを削除
                        size_t pos = it->find("  ");
                        while (pos != std::string::npos)
                        {
                            it->replace(pos, 2, " ");
                            pos = it->find("  ");
                        }

                        // Trim spaces at the beginning and end of the line
                        // 行の先頭と末尾のスペースをトリム
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
        // 変更内容をログファイルに更新
        std::string directoryPath = filePath.substr(0, filePath.find_last_of("\\/"));
        std::string logMessage = mainVersionFromLine + " -> " + newMainVersion;
        updateLogFile(directoryPath + "\\update_log.txt", fileName, logMessage, "");

        // Display the new main version line
        // 新しいメインバージョン行を表示
        std::cout << "新しいメインバージョン行： " << newMainVersionLine << std::endl;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

void updateRevision(std::vector<std::string> &fileLines, const std::string &filePath, const std::string &fileName)
{
    // Extract elements from the main version line
    // メインバージョン行から要素を抽出
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
    // 要素の説明をループを使って初期化
    std::vector<std::string> elementDescriptions(7);
    // extract first line
    // 1行目を抽出
    elementDescriptions[0] = "要素 : コンポーネント";
    elementDescriptions[1] = "要素 : 日付";
    elementDescriptions[2] = "要素 : メインバージョン";
    elementDescriptions[3] = "要素 : リビジョン";
    elementDescriptions[4] = "要素 : 識別子";
    elementDescriptions[5] = "要素 : 不明1";
    elementDescriptions[6] = "要素 : 不明2";

    std::cout << "メインバージョン行から抽出された要素：" << std::endl;
    for (size_t i = 0; i < elements.size() && i < elementDescriptions.size(); ++i)
    {
        std::cout << elementDescriptions[i] << ": " << elements[i] << std::endl;
    }

    // Step 4: Extract the revision number
    // ステップ4：リビジョン番号を抽出
    std::string currentRevision = elements[3]; // Assuming revision is at index 3 // リビジョンはインデックス3と仮定

    // Step 5: Increment the revision
    // ステップ5：リビジョン番号を増やす
    int incrementedRevision = std::stoi(currentRevision) + 1;
    std::string newRevision = (incrementedRevision < 10) ? "0" + std::to_string(incrementedRevision) : std::to_string(incrementedRevision);

    // Step 6: Create the new line with updated revision number and formatted date
    // ステップ6：更新されたリビジョン番号とフォーマットされた日付で新しい行を作成
    std::string newRevisionLine = mainVersionLine;
    size_t revisionPos = newRevisionLine.find("\"" + currentRevision + "\"");
    if (revisionPos != std::string::npos)
    {
        newRevisionLine.replace(revisionPos + 1, currentRevision.length(), newRevision);
    }

    // Update the Date element with the new formatted date
    // 新しい行の日付要素を更新
    size_t datePos = newRevisionLine.find("\"" + elements[1] + "\"");
    if (datePos != std::string::npos)
    {
        std::string currentDate = getCurrentDate();
        newRevisionLine.replace(datePos + 1, elements[1].length(), currentDate);
    }

    // Get the revision number from the new line
    // 新しい行からリビジョン番号を取得
    std::string newLineRevision = newRevision;

    // Update the Identifier element
    // 識別子要素を更新
    size_t identifierIndex = 4;                         // 識別子要素のインデックス
    std::string identifier = elements[identifierIndex]; // 識別子要素はインデックス4と仮定

    // Find the revision number in the Identifier
    // 識別子内のリビジョン番号を検索
    size_t dashPos = identifier.rfind('-');
    size_t revisionStartPos = dashPos + 1;
    size_t revisionEndPos = identifier.find("\"", revisionStartPos);
    std::string identifierRevision = identifier.substr(revisionStartPos, revisionEndPos - revisionStartPos);

    // Replace the old revision number in the Identifier with the new one from the new line
    // 識別子内の古いリビジョン番号を新しい行からのもので置換
    identifier.replace(revisionStartPos, revisionEndPos - revisionStartPos, newLineRevision);

    // Update the Identifier line in newRevisionLine
    // 新しいRevision Line内の識別子行を更新
    size_t identifierPos = newRevisionLine.find(elements[identifierIndex]);
    if (identifierPos != std::string::npos)
    {
        size_t endPos = identifierPos + elements[identifierIndex].length();
        newRevisionLine.replace(identifierPos, endPos - identifierPos, identifier);
    }

    // Insert the new revision line below the main version line
    // 新しいリビジョン行をメインバージョン行の下に挿入
    auto it = std::find(fileLines.begin(), fileLines.end(), mainVersionLine);
    if (it != fileLines.end())
    {
        // Calculate the position to insert the new revision line
        // 新しいリビジョン行を挿入する位置を計算
        size_t insertPos = std::distance(fileLines.begin(), it) + 1;

        // Insert the new revision line
        // 新しいリビジョン行を挿入
        fileLines.insert(fileLines.begin() + insertPos, newRevisionLine);
    }

    // Step 9: Add comment to the old line
    // ステップ9：古い行にコメントを追加
    for (size_t i = 0; i < fileLines.size(); ++i)
    {
        if (fileLines[i].find(mainVersionLine) != std::string::npos)
        {
            fileLines[i] = "//" + fileLines[i]; // Add "//" comment to the old line // 古い行に"//"のコメントを追加
            break;
        }
    }

    // Update the log file with the changes made
    // 変更内容をログファイルに更新
    std::string logFilePath = filePath.substr(0, filePath.find_last_of("\\/")) + "\\update_log.txt";
    updateLogFile(logFilePath, fileName, "", currentRevision + " -> " + newRevision);

    // Display the updated revision line again after logging
    // ロギング後に再度更新されたリビジョン行を表示
    std::cout << "更新されたリビジョン行 : " << newRevisionLine << std::endl;

    // Save the updated lines back to the file (as before)
    std::ofstream outputFile(filePath);
    for (const std::string &updatedLine : fileLines)
    {
        outputFile << updatedLine << "\n";
    }
    outputFile.close();

    std::cout << "リビジョンが更新されました。新しいリビジョン：" << newRevision << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//

int main()
{
    // Loop to repeatedly prompt the user for file path and options
    // ユーザーにファイルパスまたはプログラムを終了するかの選択を繰り返し提示するループ
    while (true)
    {
        // Prompt the user to enter the file path or quit the program
        // ユーザーにファイルパスを入力させるか、プログラムを終了させるかを尋ねる
        std::cout << "ファイルパスを入力してください（または '0' または 'q' を入力してプログラムを終了）：";
        std::string filePath;
        std::getline(std::cin, filePath);

        // Check if the user wants to quit the program
        // プログラムを終了するかどうかを確認
        if (filePath == "0" || filePath == "q")
        {
            std::cout << "Quitting the program." << std::endl;
            break;
        }

        // Check if the specified file exists
        // 指定されたファイルが存在するかを確認
        if (!fileExists(filePath))
        {
            std::cout << "File not found at the specified path." << std::endl;
            continue; // Skip to the next iteration of the loop
        }

        // Extract the file name from the file path
        std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);

        // Read the contents of the file into a vector of strings (each line as an element)
        // ファイルの内容を読み込み、各行を要素とする文字列ベクタに格納

        std::vector<std::string> fileLines;
        std::string line;
        std::ifstream inputFile(filePath);
        while (std::getline(inputFile, line))
        {
            fileLines.push_back(line);
        }
        inputFile.close();

        // Find the main version line in the file
        // ファイル内でメインバージョン行を検索
        std::string mainVersionLine = findMainVersionLine(fileLines);

        // Check if a valid main version line is found
        // 有効なメインバージョン行が見つかったかを確認
        if (!mainVersionLine.empty())
        {
            std::cout << "File found: 利用可能なファイル：" << fileName << std::endl;
            std::cout << "[ メインバージョン ]を更新するには '1' を、[ リビジョン ]を更新するには '2' を入力してください：";
            int option;
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

            // Check the chosen option
            // 選択されたオプションを確認
            if (option == 1)
            {
                // Call the function to update the main version
                // メインバージョンを更新する関数を呼び出す
                updateMainVersion(fileLines, filePath, fileName);

                // Write the updated lines back to the file
                // 更新された行をファイルに書き込む
                std::ofstream outputFile(filePath);
                for (const std::string &updatedLine : fileLines)
                {
                    outputFile << updatedLine << "\n";
                }
                outputFile.close();

                // Update the main version line after the file has been modified
                // ファイルが変更された後にメインバージョン行を更新
                mainVersionLine = findMainVersionLine(fileLines);
            }
            else if (option == 2)
            {
                // Call the function to update the revision
                // リビジョンを更新する関数を呼び出す
                updateRevision(fileLines, filePath, fileName);

                // Write the updated lines back to the file
                // 更新された行をファイルに書き込む
                std::ofstream outputFile(filePath);
                for (const std::string &updatedLine : fileLines)
                {
                    outputFile << updatedLine << "\n";
                }
                outputFile.close();
            }

            else
            {
                std::cout << "無効なオプションです。'1' または '2' を選択してください。" << std::endl;
            }
        }
        else
        {
            std::cout << "ファイル内で有効なメインバージョン行が見つかりません。" << std::endl;
        }

        // Ask the user if they want to continue or quit the program
        // ユーザーに続行するかプログラムを終了するかを尋ねる
        std::cout << "続行しますか？（プログラムを終了するには '0' または 'q' を押し、続行するには他のキーを押してください）：";
        std::string quitChoice;
        std::getline(std::cin, quitChoice);

        // Check if the user wants to quit the program
        // プログラムを終了するかどうかを確認
        if (quitChoice == "0" || quitChoice == "q")
        {
            std::cout << "Quitting the program. プログラムを終了します。" << std::endl;
            break;
        }
    } // End of while loop // ループの終わり

    return 0;
}