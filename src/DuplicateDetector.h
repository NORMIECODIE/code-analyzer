#pragma once

#include <string>
#include <vector>
#include "CodeParser.h"

// Represents one piece of duplicate code.
struct DuplicateMatch {
    std::string firstFile;
    std::string secondFile;
    std::string code;
};

// Detects repeated code between analyzed files.
class DuplicateDetector {
public:
    static std::vector<DuplicateMatch> findDuplicates(
        const std::vector<FileStats>& allStats
    );
};