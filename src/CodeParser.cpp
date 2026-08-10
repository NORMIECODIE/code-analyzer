#include "CodeParser.h"
#include <fstream>
#include <sstream>

// Heuristic only: looks for a line containing "(" and ")" and ending in "{",
// which roughly matches function definitions like "int foo(int x) {".
// This will have false positives/negatives — real parsing comes later with libclang.
bool CodeParser::looksLikeFunctionDeclaration(const std::string& line) const {
    bool hasParens = line.find('(') != std::string::npos &&
                      line.find(')') != std::string::npos;

    // Trim trailing whitespace to check the last real character.
    std::string trimmed = line;
    while (!trimmed.empty() && std::isspace(static_cast<unsigned char>(trimmed.back()))) {
        trimmed.pop_back();
    }

    bool endsWithBrace = !trimmed.empty() && trimmed.back() == '{';

    return hasParens && endsWithBrace;
}

FileStats CodeParser::analyzeFile(const std::string& filePath) const {
    FileStats stats;
    stats.filePath = filePath;

    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        stats.totalLines++;

        if (looksLikeFunctionDeclaration(line)) {
            stats.functionCount++;
        }

        if (line.find("TODO") != std::string::npos) {
            stats.todoCount++;
        }
    }

    return stats;
}
