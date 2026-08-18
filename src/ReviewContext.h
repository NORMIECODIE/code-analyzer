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

    // Overall quality score.
    int qualityScore = 100;

    // Total number of quality issues.
    int totalIssues = 0;
};
int calculateQualityScore(
    const std::vector<FileStats>& allStats
);

ReviewContext buildReviewContext(
    const std::string& projectPath,
    const std::vector<std::string>& files,
    const std::vector<FileStats>& allStats,
    const std::vector<DuplicateMatch>& duplicates
);