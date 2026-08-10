#include "Report.h"
#include <iostream>
#include <iomanip>

void Report::print(const std::vector<FileStats>& allStats) {
    int totalLines = 0;
    int totalFunctions = 0;
    int totalTodos = 0;

    std::cout << "\n=== Code Analysis Report ===\n\n";

    for (const auto& stats : allStats) {
        std::cout << std::left << std::setw(40) << stats.filePath
                  << "| " << stats.totalLines << " lines"
                  << " | " << stats.functionCount << " functions"
                  << " | " << stats.todoCount << " TODOs\n";

        totalLines += stats.totalLines;
        totalFunctions += stats.functionCount;
        totalTodos += stats.todoCount;
    }

    std::cout << "\n-----------------------------\n";
    std::cout << "Files scanned:   " << allStats.size() << "\n";
    std::cout << "Total lines:     " << totalLines << "\n";
    std::cout << "Total functions: " << totalFunctions << "\n";
    std::cout << "Total TODOs:     " << totalTodos << "\n\n";
}
