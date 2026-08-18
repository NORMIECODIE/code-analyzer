#include "Report.h"
#include <iostream>
#include <iomanip>

void Report::print(
    const std::vector<FileStats>& allStats,
    const std::vector<DuplicateMatch>& duplicates
) {

    int totalLines = 0;
    int totalFunctions = 0;
    int totalTodos = 0;

    std::string projectLongestFunction;
    std::string projectLongestFile;
    int projectLongestFunctionLines = 0;

    std::cout << "\n=== Code Analysis Report ===\n\n";

    for (const auto& stats : allStats) {

        std::cout << std::left << std::setw(40)
                  << stats.filePath
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

        // Display large function warning.
        if (!stats.largeFunctionName.empty()) {

            std::cout << "    WARNING: Large function: "
                      << stats.largeFunctionName
                      << " | "
                      << stats.largeFunctionLines
                      << " lines\n";
        }

        // Display complexity information.
        if (!stats.complexFunctionName.empty()) {

            std::cout << "    Complexity: "
                      << stats.complexFunctionName
                      << " | Score: "
                      << stats.complexFunctionScore
                      << "\n";
        }

        totalLines += stats.totalLines;
        totalFunctions += stats.functionCount;
        totalTodos += stats.todoCount;

        // Check for the longest function in the entire project.
        if (stats.longestFunctionLines >
            projectLongestFunctionLines) {

            projectLongestFunctionLines =
                stats.longestFunctionLines;

            projectLongestFunction =
                stats.longestFunctionName;

            projectLongestFile =
                stats.filePath;
        }
    }

    std::cout << "\n-----------------------------\n";

    std::cout << "Files scanned:   "
              << allStats.size()
              << "\n";

    std::cout << "Total lines:     "
              << totalLines
              << "\n";

    std::cout << "Total functions: "
              << totalFunctions
              << "\n";

    std::cout << "Total TODOs:     "
              << totalTodos
              << "\n";

    // Display project-wide longest function.
    if (!projectLongestFunction.empty()) {

        std::cout << "Longest function: "
                  << projectLongestFunction
                  << " ("
                  << projectLongestFunctionLines
                  << " lines)\n";

        std::cout << "Longest function file: "
                  << projectLongestFile
                  << "\n";
    }

    // -----------------------------------------
    // CODE QUALITY ISSUES
    // -----------------------------------------

    bool hasIssues = false;

    for (const auto& stats : allStats) {

        if (!stats.issues.empty()) {

            hasIssues = true;
            break;
        }
    }

    if (hasIssues) {

        std::cout << "\n=== Code Quality Issues ===\n\n";

        for (const auto& stats : allStats) {

            for (const auto& issue : stats.issues) {

                std::cout << "Issue: "
                          << issue.type;

                if (!issue.severity.empty()) {

                    std::cout << " | Severity: "
                              << issue.severity;
                }

                std::cout << "\n";

                std::cout << "    File: "
                          << issue.filePath
                          << "\n";

                // Display related file.
                if (!issue.relatedFilePath.empty()) {

                    std::cout << "    Related file: "
                              << issue.relatedFilePath
                              << "\n";
                }

                // Display function.
                if (!issue.functionName.empty()) {

                    std::cout << "    Function: "
                              << issue.functionName
                              << "\n";
                }

                // Display numeric value.
                if (issue.value > 0) {

                    if (issue.type ==
                        "Large Function") {

                        std::cout << "    Lines: "
                                  << issue.value
                                  << "\n";

                    }
                    else if (issue.type ==
                             "High Complexity") {

                        std::cout << "    Complexity score: "
                                  << issue.value
                                  << "\n";

                    }
                    else if (issue.type ==
                             "Duplicate Code") {

                        std::cout << "    Lines duplicated: "
                                  << issue.value
                                  << "\n";

                    }
                    else if (issue.type == "TODO" ||
                             issue.type == "FIXME") {

                        std::cout << "    Occurrences: "
                                  << issue.value
                                  << "\n";

                    }
                    else {

                        std::cout << "    Value: "
                                  << issue.value
                                  << "\n";
                    }
                }

                std::cout << "    Problem: "
                          << issue.message
                          << "\n";

                std::cout << "    Suggestion: "
                          << issue.suggestion
                          << "\n\n";
            }
        }

    } else {

        std::cout << "\n=== Code Quality Issues ===\n\n";

        std::cout << "No code quality issues found.\n";
    }

    // -----------------------------------------
    // QUALITY SUMMARY
    // -----------------------------------------

    int totalIssues = 0;

    int highSeverity = 0;
    int mediumSeverity = 0;
    int lowSeverity = 0;

    int largeFunctionIssues = 0;
    int complexityIssues = 0;
    int duplicateCodeIssues = 0;
    int todoIssues = 0;
    int fixmeIssues = 0;

    for (const auto& stats : allStats) {

        for (const auto& issue : stats.issues) {

            totalIssues++;

            // Count severity.
            if (issue.severity == "HIGH") {

                highSeverity++;

            }
            else if (issue.severity == "MEDIUM") {

                mediumSeverity++;

            }
            else if (issue.severity == "LOW") {

                lowSeverity++;
            }

            // Count issue types.
            if (issue.type == "Large Function") {

                largeFunctionIssues++;

            }
            else if (issue.type == "High Complexity") {

                complexityIssues++;

            }
            else if (issue.type == "Duplicate Code") {

                duplicateCodeIssues++;

            }
            else if (issue.type == "TODO") {

                todoIssues++;

            }
            else if (issue.type == "FIXME") {

                fixmeIssues++;
            }
        }
    }

    std::cout << "\n=== Quality Summary ===\n\n";

    std::cout << "Total issues:        "
              << totalIssues
              << "\n";

    std::cout << "High severity:      "
              << highSeverity
              << "\n";

    std::cout << "Medium severity:    "
              << mediumSeverity
              << "\n";

    std::cout << "Low severity:       "
              << lowSeverity
              << "\n\n";

    std::cout << "Large functions:    "
              << largeFunctionIssues
              << "\n";

    std::cout << "High complexity:    "
              << complexityIssues
              << "\n";

    std::cout << "Duplicate code:     "
              << duplicateCodeIssues
              << "\n";

    std::cout << "TODOs:              "
              << todoIssues
              << "\n";

    std::cout << "FIXMEs:             "
              << fixmeIssues
              << "\n";

    // -----------------------------------------
    // QUALITY SCORE
    // -----------------------------------------

    int qualityScore = 100;

    // Calculate quality score based on issue type.
for (const auto& stats : allStats) {

    for (const auto& issue : stats.issues) {

        if (issue.type == "High Complexity") {

            qualityScore -= 12;

        }
        else if (issue.type == "FIXME") {

            qualityScore -= 10;

        }
        else if (issue.type == "Large Function") {

            qualityScore -= 8;

        }
        else if (issue.type == "Duplicate Code") {

            qualityScore -= 8;

        }
        else if (issue.type == "TODO") {

            qualityScore -= 5;

        }
        else if (issue.severity == "HIGH") {

            qualityScore -= 20;

        }
        else if (issue.severity == "MEDIUM") {

            qualityScore -= 10;

        }
        else if (issue.severity == "LOW") {

            qualityScore -= 5;
        }
    }
}

    // Prevent the score from going below zero.
    if (qualityScore < 0) {

        qualityScore = 0;
    }

    std::string qualityRating;

    if (qualityScore >= 90) {

        qualityRating = "Excellent";

    }
    else if (qualityScore >= 75) {

        qualityRating = "Good";

    }
    else if (qualityScore >= 50) {

        qualityRating = "Needs Improvement";

    }
    else {

        qualityRating = "Poor";
    }

    std::cout << "\n=== Quality Score ===\n\n";

    std::cout << "Score:  "
              << qualityScore
              << " / 100\n";

    std::cout << "Rating: "
              << qualityRating
              << "\n";

    // -----------------------------------------
    // DUPLICATE CODE DETAILS
    // -----------------------------------------

    if (!duplicates.empty()) {

        std::cout << "\n=== Duplicate Code ===\n\n";

        for (const auto& duplicate : duplicates) {

            std::cout << "Duplicate block:\n";

            for (const auto& line : duplicate.codeLines) {

                std::cout << "    "
                          << line
                          << "\n";
            }

            std::cout << "\nLines duplicated: "
                      << duplicate.codeLines.size()
                      << "\n";

            std::cout << "Found in:\n";

            std::cout << "    "
                      << duplicate.firstFile
                      << "\n";

            std::cout << "    "
                      << duplicate.secondFile
                      << "\n\n";
        }

    } else {

        std::cout << "\nNo duplicate code found.\n";
    }
}