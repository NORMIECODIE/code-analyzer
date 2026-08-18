#pragma once

#include <string>
#include <vector>

#include "CodeParser.h"
#include "QualityIssue.h"
#include "DuplicateDetector.h"

// Contains all information needed for an AI code review.
struct ReviewContext {

    // Project being analyzed.
    std::string projectPath;

    // Files analyzed in the project.
    std::vector<std::string> files;

    // Statistics for each source file.
    std::vector<FileStats> fileStats;

    // Detected duplicate code blocks.
    std::vector<DuplicateMatch> duplicates;

    // Complete source code of each analyzed file.
    std::vector<std::string> sourceCode;

    // Overall quality score.
    int qualityScore = 100;

    // Total number of quality issues.
    int totalIssues = 0;
};

// Calculate the overall quality score.
int calculateQualityScore(
    const std::vector<FileStats>& allStats
);

// Build the complete context for an AI code review.
ReviewContext buildReviewContext(
    const std::string& projectPath,
    const std::vector<std::string>& files,
    const std::vector<FileStats>& allStats,
    const std::vector<DuplicateMatch>& duplicates
);