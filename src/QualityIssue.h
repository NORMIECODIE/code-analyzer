#pragma once

#include <string>

// Represents one code-quality issue found by the analyzer.
struct QualityIssue {

    // Type of issue.
    // Examples:
    // "Large Function"
    // "High Complexity"
    // "Duplicate Code"
    std::string type;

    // Main file where the issue was found.
    std::string filePath;

    // Related file, if the issue involves another file.
    // Used mainly for duplicate code detection.
    std::string relatedFilePath;

    // Function related to the issue, if applicable.
    std::string functionName;

    // Numeric value associated with the issue.
    //
    // Examples:
    // Large Function  -> number of lines
    // High Complexity -> complexity score
    // Duplicate Code  -> duplicated lines
    int value = 0;

    // Short explanation of the problem.
    std::string message;

    // Suggested improvement.
    std::string suggestion;

    // Severity of the issue.
    // Examples:
    // LOW
    // MEDIUM
    // HIGH
    std::string severity;
};