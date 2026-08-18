#pragma once

#include <string>
#include <vector>
#include "CodeParser.h"
#include "QualityIssue.h"

// Represents one piece of duplicate code.
struct DuplicateMatch {

    std::string firstFile;
    std::string secondFile;

    // Lines that are duplicated.
    std::vector<std::string> codeLines;
};

// Detects repeated code between analyzed files.
class DuplicateDetector {

public:

    static std::vector<DuplicateMatch> findDuplicates(
        const std::vector<FileStats>& allStats
    );

    // Converts duplicate matches into structured
    // code-quality issues.
    static std::vector<QualityIssue> createIssues(
        const std::vector<DuplicateMatch>& duplicates
    );
};