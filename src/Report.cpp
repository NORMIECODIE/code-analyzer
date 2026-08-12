#include "Report.h"
#include <iostream>
#include <iomanip>

void Report::print(const std::vector<FileStats>& allStats) {

    int totalLines = 0;
    int totalFunctions = 0;
    int totalTodos = 0;

    std::string projectLongestFunction;
    std::string projectLongestFile;
    int projectLongestFunctionLines = 0;

    std::cout << "\n=== Code Analysis Report ===\n\n";

    for (const auto& stats : allStats) {

        std::cout << std::left << std::setw(40) << stats.filePath
                  << "| " << stats.totalLines << " lines"
                  << " | " << stats.functionCount << " functions"
                  << " | " << stats.todoCount << " TODOs\n";

        // Display the longest function in this file.
        if (!stats.longestFunctionName.empty()) {
            std::cout << "    Longest function: "
                      << stats.longestFunctionName
                      << " | "
                      << stats.longestFunctionLines
                      << " lines\n";
        }

        totalLines += stats.totalLines;
        totalFunctions += stats.functionCount;
        totalTodos += stats.todoCount;

        // Check whether this is the longest function in the project.
        if (stats.longestFunctionLines > projectLongestFunctionLines) {

            projectLongestFunctionLines = stats.longestFunctionLines;
            projectLongestFunction = stats.longestFunctionName;
            projectLongestFile = stats.filePath;
        }
    }

    std::cout << "\n-----------------------------\n";

    std::cout << "Files scanned:   " << allStats.size() << "\n";
    std::cout << "Total lines:     " << totalLines << "\n";
    std::cout << "Total functions: " << totalFunctions << "\n";
    std::cout << "Total TODOs:     " << totalTodos << "\n";

    // Display the longest function in the entire project.
    if (!projectLongestFunction.empty()) {

        std::cout << "Longest function: "
                  << projectLongestFunction
                  << " (" << projectLongestFunctionLines
                  << " lines)\n";

        std::cout << "Longest function file: "
                  << projectLongestFile << "\n";
    }

    std::cout << "\n";
}