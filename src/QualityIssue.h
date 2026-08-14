#pragma once

#include <string>

// Represents one code-quality issue found by the analyzer.
struct QualityIssue {

    // Name of the issue.
    std::string type;

    // File where the issue was found.
    std::string filePath;

    // Function related to the issue, if applicable.
    std::string functionName;

    // Short explanation of the problem.
    std::string message;

    // Suggested improvement.
    std::string suggestion;
};