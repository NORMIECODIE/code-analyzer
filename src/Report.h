#pragma once
#include <vector>
#include "CodeParser.h"

class Report {
public:
    static void print(const std::vector<FileStats>& allStats);
};
