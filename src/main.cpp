#include <iostream>
#include "FileScanner.h"
#include "CodeParser.h"
#include "Report.h"
#include "DuplicateDetector.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: analyzer <path-to-project>\n";
        return 1;
    }

    std::string targetPath = argv[1];

    FileScanner scanner(targetPath);
    std::vector<std::string> files = scanner.findSourceFiles();

    if (files.empty()) {
        std::cout << "No source files found in: " << targetPath << "\n";
        return 0;
    }

    CodeParser parser;
    std::vector<FileStats> allStats;

        for (const auto& file : files) {
        allStats.push_back(parser.analyzeFile(file));
    }

    // Find duplicate code between analyzed files.
    std::vector<DuplicateMatch> duplicates =
        DuplicateDetector::findDuplicates(allStats);

    Report::print(allStats, duplicates);

    return 0;
}
