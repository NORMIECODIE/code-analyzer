#include "ReviewContext.h"

// Calculate the overall quality score from the detected issues.
int calculateQualityScore(
    const std::vector<FileStats>& allStats
) {

    int score = 100;

    for (const auto& stats : allStats) {

        for (const auto& issue : stats.issues) {

            if (issue.type == "High Complexity") {

                score -= 12;

            }
            else if (issue.type == "FIXME") {

                score -= 10;

            }
            else if (issue.type == "Large Function") {

                score -= 8;

            }
            else if (issue.type == "Duplicate Code") {

                score -= 8;

            }
            else if (issue.type == "TODO") {

                score -= 5;

            }
            else if (issue.severity == "HIGH") {

                score -= 20;

            }
            else if (issue.severity == "MEDIUM") {

                score -= 10;

            }
            else if (issue.severity == "LOW") {

                score -= 5;
            }
        }
    }

    if (score < 0) {
        score = 0;
    }

    return score;
}


// Build the information that will eventually be sent
// to the AI review layer.
ReviewContext buildReviewContext(
    const std::string& projectPath,
    const std::vector<std::string>& files,
    const std::vector<FileStats>& allStats,
    const std::vector<DuplicateMatch>& duplicates
) {

    ReviewContext context;

    context.projectPath = projectPath;
    context.files = files;
    context.fileStats = allStats;
    context.duplicates = duplicates;

    context.qualityScore =
        calculateQualityScore(allStats);

    for (const auto& stats : allStats) {

        context.totalIssues +=
            static_cast<int>(stats.issues.size());
    }

    return context;
}