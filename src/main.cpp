#include <iostream>

#include "FileScanner.h"
#include "CodeParser.h"
#include "Report.h"
#include "DuplicateDetector.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {

        std::cerr
            << "Usage: analyzer <path-to-project>\n";

        return 1;
    }

    std::string targetPath =
        argv[1];

    // Scan the target project.
    FileScanner scanner(targetPath);

    std::vector<std::string> files =
        scanner.findSourceFiles();

    if (files.empty()) {

        std::cout
            << "No source files found in: "
            << targetPath
            << "\n";

        return 0;
    }

    // Analyze each source file.
    CodeParser parser;

    std::vector<FileStats> allStats;

    for (const auto& file : files) {

        allStats.push_back(
            parser.analyzeFile(file)
        );
    }

    // Find duplicate code blocks.
    std::vector<DuplicateMatch> duplicates =
        DuplicateDetector::findDuplicates(
            allStats
        );

    // Convert duplicate blocks into
    // structured quality issues.
    std::vector<QualityIssue> duplicateIssues =
        DuplicateDetector::createIssues(
            duplicates
        );

    // Add duplicate issues to the first
    // related file's issue list.
    for (size_t i = 0;
         i < duplicateIssues.size();
         i++) {

        const auto& issue =
            duplicateIssues[i];

        for (auto& stats : allStats) {

            if (stats.filePath ==
                issue.filePath) {

                stats.issues.push_back(
                    issue
                );

                break;
            }
        }
    }

    // Generate the final report.
    Report::print(
        allStats,
        duplicates
    );

    return 0;
}