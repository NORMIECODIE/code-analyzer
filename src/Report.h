#pragma once

#include <vector>
#include "CodeParser.h"
#include "DuplicateDetector.h"

class Report {
public:
    static void print(
        const std::vector<FileStats>& allStats,
        const std::vector<DuplicateMatch>& duplicates
    );
};