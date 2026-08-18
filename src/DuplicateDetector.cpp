#include "DuplicateDetector.h"

// Find duplicate code blocks between analyzed files.
std::vector<DuplicateMatch> DuplicateDetector::findDuplicates(
    const std::vector<FileStats>& allStats) {

    std::vector<DuplicateMatch> duplicates;

    for (size_t i = 0; i < allStats.size(); i++) {

        for (size_t j = i + 1; j < allStats.size(); j++) {

            const auto& fileA = allStats[i];
            const auto& fileB = allStats[j];

            // Compare every line from file A with file B.
            for (size_t a = 0; a < fileA.codeLines.size(); a++) {

                for (size_t b = 0; b < fileB.codeLines.size(); b++) {

                    if (fileA.codeLines[a] ==
                        fileB.codeLines[b]) {

                        // Start building a duplicate block.
                        std::vector<std::string> block;

                        size_t currentA = a;
                        size_t currentB = b;

                        // Find consecutive matching lines.
                        while (
                            currentA < fileA.codeLines.size() &&
                            currentB < fileB.codeLines.size() &&
                            fileA.codeLines[currentA] ==
                                fileB.codeLines[currentB]
                        ) {

                            block.push_back(
                                fileA.codeLines[currentA]
                            );

                            currentA++;
                            currentB++;
                        }

                        // Only consider blocks with at least
                        // 2 duplicated lines.
                        if (block.size() >= 2) {

                            DuplicateMatch match;

                            match.firstFile =
                                fileA.filePath;

                            match.secondFile =
                                fileB.filePath;

                            match.codeLines =
                                block;

                            duplicates.push_back(match);

                            // Skip ahead to avoid repeatedly
                            // detecting the same block.
                            a = currentA - 1;

                            break;
                        }
                    }
                }
            }
        }
    }

    return duplicates;
}


// Convert duplicate matches into QualityIssue objects.
std::vector<QualityIssue>
DuplicateDetector::createIssues(
    const std::vector<DuplicateMatch>& duplicates) {

    std::vector<QualityIssue> issues;

    for (const auto& duplicate : duplicates) {

        QualityIssue issue;

        issue.type =
            "Duplicate Code";

        issue.filePath =
            duplicate.firstFile;

        issue.relatedFilePath =
            duplicate.secondFile;

        issue.value =
            static_cast<int>(
                duplicate.codeLines.size()
            );

        issue.message =
            "A block of " +
            std::to_string(issue.value) +
            " consecutive lines is duplicated "
            "across multiple files.";

        issue.suggestion =
            "Extract the repeated code into a shared "
            "function or reusable component.";

        // Four or more duplicated lines are considered
        // a medium-severity issue.
        if (issue.value >= 4) {

            issue.severity =
                "MEDIUM";

        } else {

            issue.severity =
                "LOW";
        }

        issues.push_back(issue);
    }

    return issues;
}