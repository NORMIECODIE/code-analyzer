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

        if (looksLikeFunctionDeclaration(line)) {

            stats.functionCount++;
            insideFunction = true;
            currentFunctionLines = 1;
            braceDepth = 0;

            size_t openParen = line.find('(');

            if (openParen != std::string::npos) {

                std::string beforeParen = line.substr(0, openParen);

                size_t end = beforeParen.find_last_not_of(" \t");

                if (end != std::string::npos) {
                    beforeParen = beforeParen.substr(0, end + 1);
                }

                size_t space = beforeParen.find_last_of(" \t");

                if (space != std::string::npos) {
                    currentFunctionName =
                        beforeParen.substr(space + 1);
                } else {
                    currentFunctionName = beforeParen;
                }
            }
        }
        else if (insideFunction) {

            currentFunctionLines++;
        }

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

            if (currentFunctionLines > stats.longestFunctionLines) {

                stats.longestFunctionLines = currentFunctionLines;
                stats.longestFunctionName = currentFunctionName;
            }

            insideFunction = false;
        }
    }

    return stats;
}