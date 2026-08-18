#include <iostream>

#include "FileScanner.h"
#include "CodeParser.h"
#include "Report.h"
#include "DuplicateDetector.h"
#include "ReviewContext.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {

        std::cerr
            << "Usage: analyzer <path-to-project>\n";

        return 1;
    }

    std::string targetPath =
        argv[1];

    // -----------------------------------------
    // SCAN PROJECT
    // -----------------------------------------

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

    // -----------------------------------------
    // ANALYZE SOURCE FILES
    // -----------------------------------------

    CodeParser parser;

    std::vector<FileStats> allStats;

    for (const auto& file : files) {

        allStats.push_back(
            parser.analyzeFile(file)
        );
    }

    // -----------------------------------------
    // FIND DUPLICATE CODE
    // -----------------------------------------

    std::vector<DuplicateMatch> duplicates =
        DuplicateDetector::findDuplicates(
            allStats
        );

    // -----------------------------------------
    // CREATE DUPLICATE QUALITY ISSUES
    // -----------------------------------------

    std::vector<QualityIssue> duplicateIssues =
        DuplicateDetector::createIssues(
            duplicates
        );

    // Add duplicate issues to the
    // corresponding file.
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

    // -----------------------------------------
    // BUILD AI REVIEW CONTEXT
    // -----------------------------------------

    ReviewContext reviewContext =
        buildReviewContext(
            targetPath,
            files,
            allStats,
            duplicates
        );

    // -----------------------------------------
    // DISPLAY CONTEXT INFORMATION
    // -----------------------------------------

    std::cout << "\n=== Review Context ===\n\n";

    std::cout << "Project: "
              << reviewContext.projectPath
              << "\n";

    std::cout << "Files included: "
              << reviewContext.files.size()
              << "\n";

    std::cout << "Total issues: "
              << reviewContext.totalIssues
              << "\n";

    std::cout << "Quality score: "
              << reviewContext.qualityScore
              << " / 100\n";

    std::cout << "Duplicate blocks: "
              << reviewContext.duplicates.size()
              << "\n";

    // -----------------------------------------
    // GENERATE FINAL REPORT
    // -----------------------------------------

    Report::print(
        allStats,
        duplicates
    );

    return 0;
}