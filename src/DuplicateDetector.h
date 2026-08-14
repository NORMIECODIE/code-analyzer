#pragma once

#include <string>
#include <vector>
#include "CodeParser.h"

// Represents a block of duplicate code.
struct DuplicateMatch {
    std::string firstFile;
    std::string secondFile;
    std::vector<std::string> codeLines;
};

// Detects repeated blocks of code between analyzed files.
class DuplicateDetector {
public:
    static std::vector<DuplicateMatch> findDuplicates(
        const std::vector<FileStats>& allStats
    );
};