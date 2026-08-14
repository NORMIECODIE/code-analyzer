#pragma once

#include <string>
#include <vector>

// Result of analyzing a single source file.
struct FileStats {
    std::string filePath;
    int totalLines = 0;
    int functionCount = 0;
    int todoCount = 0;

    std::string longestFunctionName;
    int longestFunctionLines = 0;

    std::string largeFunctionName;
    int largeFunctionLines = 0;

    std::vector<std::string> codeLines;
};

// Very simple line-based analysis (not a real parser yet — that's a later upgrade).
class CodeParser {
public:
    FileStats analyzeFile(const std::string& filePath) const;

private:
    bool looksLikeFunctionDeclaration(const std::string& line) const;
};