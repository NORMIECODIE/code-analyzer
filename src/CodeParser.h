#pragma once

#include <string>
#include <vector>
#include "QualityIssue.h"

// Result of analyzing a single source file.
struct FileStats {

    std::string filePath;

    int totalLines = 0;
    int functionCount = 0;
    int todoCount = 0;

    // Longest function information.
    std::string longestFunctionName;
    int longestFunctionLines = 0;

    // Large function information.
    std::string largeFunctionName;
    int largeFunctionLines = 0;

    // Complexity information.
    std::string complexFunctionName;
    int complexFunctionScore = 0;

    // Structured code-quality issues.
    std::vector<QualityIssue> issues;

    // Normalized source-code lines.
    std::vector<std::string> codeLines;
};


// Very simple line-based analysis
// (not a real parser yet — that's a later upgrade).
class CodeParser {

public:

    FileStats analyzeFile(
        const std::string& filePath
    ) const;

private:

    bool looksLikeFunctionDeclaration(
        const std::string& line
    ) const;
};