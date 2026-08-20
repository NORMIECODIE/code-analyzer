#include "AIReviewEngine.h"

#include <sstream>

std::string AIReviewEngine::buildReviewPrompt(
    const ReviewContext& context
) {

    std::stringstream prompt;

    prompt
        << "You are an expert software engineer performing a code review.\n\n";

    prompt
        << "Project Path: "
        << context.projectPath
        << "\n";

    prompt
        << "Files Analyzed: "
        << context.files.size()
        << "\n";

    prompt
        << "Total Issues: "
        << context.totalIssues
        << "\n";

    prompt
        << "Quality Score: "
        << context.qualityScore
        << " / 100\n\n";

    prompt
        << "Review the following code analysis results and provide:\n"
        << "1. Overall assessment of the project.\n"
        << "2. Most important problems.\n"
        << "3. Explanation of why these problems matter.\n"
        << "4. Specific recommendations for improvement.\n"
        << "5. Suggestions for improving architecture and code quality.\n\n";

    prompt
        << "=== DETECTED ISSUES ===\n\n";

    for (const auto& stats : context.fileStats) {

        prompt
            << "File: "
            << stats.filePath
            << "\n";

        for (const auto& issue : stats.issues) {

            prompt
                << "- Type: "
                << issue.type
                << "\n";

            prompt
                << "  Severity: "
                << issue.severity
                << "\n";

            if (!issue.functionName.empty()) {

                prompt
                    << "  Function: "
                    << issue.functionName
                    << "\n";
            }

            prompt
                << "  Problem: "
                << issue.message
                << "\n";

            prompt
                << "  Current suggestion: "
                << issue.suggestion
                << "\n\n";
        }
    }

    prompt
        << "=== SOURCE CODE ===\n\n";

    for (size_t i = 0;
         i < context.files.size() &&
         i < context.sourceCode.size();
         i++) {

        prompt
            << "FILE: "
            << context.files[i]
            << "\n\n";

        prompt
            << context.sourceCode[i]
            << "\n\n";
    }

    prompt
        << "Provide a practical code review. "
        << "Prioritize important issues and avoid repeating "
        << "the same recommendation unnecessarily.\n";

    return prompt.str();
}