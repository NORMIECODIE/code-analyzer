#include "CodeParser.h"
#include <fstream>
#include <cctype>
#include <string>

// Heuristic function detection.
// It looks for something that resembles a function definition,
// while ignoring control statements such as if, for, while and switch.
bool CodeParser::looksLikeFunctionDeclaration(const std::string& line) const {

    // Make a copy of the line.
    std::string trimmed = line;

    // Remove spaces/tabs from the beginning.
    size_t start = trimmed.find_first_not_of(" \t");

    if (start != std::string::npos) {
        trimmed = trimmed.substr(start);
    }

    // Remove spaces/tabs from the end.
    size_t end = trimmed.find_last_not_of(" \t");

    if (end != std::string::npos) {
        trimmed = trimmed.substr(0, end + 1);
    }

    // Check for parentheses.
    bool hasParens =
        trimmed.find('(') != std::string::npos &&
        trimmed.find(')') != std::string::npos;

    // Check that the line ends with {
    bool endsWithBrace =
        !trimmed.empty() &&
        trimmed.back() == '{';

    // Ignore control statements.
    if (trimmed.rfind("if(", 0) == 0 ||
        trimmed.rfind("if (", 0) == 0 ||
        trimmed.rfind("for(", 0) == 0 ||
        trimmed.rfind("for (", 0) == 0 ||
        trimmed.rfind("while(", 0) == 0 ||
        trimmed.rfind("while (", 0) == 0 ||
        trimmed.rfind("switch(", 0) == 0 ||
        trimmed.rfind("switch (", 0) == 0) {

        return false;
    }

    return hasParens && endsWithBrace;
}


FileStats CodeParser::analyzeFile(const std::string& filePath) const {

    FileStats stats;
    stats.filePath = filePath;

    std::ifstream file(filePath);
    std::string line;

    bool insideFunction = false;
    int currentFunctionLines = 0;
    int braceDepth = 0;
    std::string currentFunctionName;

    while (std::getline(file, line)) {

        stats.totalLines++;

        // Store normalized non-empty lines for duplicate code detection.
        std::string normalizedLine = line;

        // Remove leading spaces and tabs.
        size_t start = normalizedLine.find_first_not_of(" \t");

        if (start != std::string::npos) {
            normalizedLine = normalizedLine.substr(start);
        }

        // Remove trailing spaces and tabs.
        size_t end = normalizedLine.find_last_not_of(" \t");

        if (end != std::string::npos) {
            normalizedLine = normalizedLine.substr(0, end + 1);
        }

        // Store the normalized line.
        if (!normalizedLine.empty()) {
            stats.codeLines.push_back(normalizedLine);
        }

        // Detect functions.
        if (looksLikeFunctionDeclaration(line)) {

            stats.functionCount++;
            insideFunction = true;
            currentFunctionLines = 1;
            braceDepth = 0;

            // Find the opening parenthesis.
            size_t openParen = line.find('(');

            if (openParen != std::string::npos) {

                std::string beforeParen =
                    line.substr(0, openParen);

                // Remove trailing spaces.
                size_t functionEnd =
                    beforeParen.find_last_not_of(" \t");

                if (functionEnd != std::string::npos) {
                    beforeParen =
                        beforeParen.substr(0, functionEnd + 1);
                }

                // Find the last space before the function name.
                size_t space =
                    beforeParen.find_last_of(" \t");

                if (space != std::string::npos) {
                    currentFunctionName =
                        beforeParen.substr(space + 1);
                }
                else {
                    currentFunctionName = beforeParen;
                }
            }
        }
        else if (insideFunction) {

            currentFunctionLines++;
        }

        // Count TODOs.
        if (line.find("TODO") != std::string::npos) {
            stats.todoCount++;
        }

        // Count opening braces.
        for (char character : line) {

            if (character == '{') {
                braceDepth++;
            }
        }

        // Count closing braces.
        for (char character : line) {

            if (character == '}') {
                braceDepth--;
            }
        }

        // Function ends when all braces are closed.
        if (insideFunction && braceDepth == 0) {

            // Update longest function.
            if (currentFunctionLines >
                stats.longestFunctionLines) {

                stats.longestFunctionLines =
                    currentFunctionLines;

                stats.longestFunctionName =
                    currentFunctionName;
            }

            // Flag functions larger than 20 lines.
            if (currentFunctionLines > 20) {

                if (currentFunctionLines >
                    stats.largeFunctionLines) {

                    stats.largeFunctionLines =
                        currentFunctionLines;

                    stats.largeFunctionName =
                        currentFunctionName;
                }
            }

            insideFunction = false;
        }
    }

    return stats;
}