#include "DuplicateDetector.h"

// Check whether a line is meaningful enough to report.
bool isMeaningfulCodeLine(const std::string& line) {

    if (line.empty()) {
        return false;
    }

    // Ignore braces.
    if (line == "{" || line == "}") {
        return false;
    }

    // Ignore preprocessor directives such as #include.
    if (line[0] == '#') {
        return false;
    }

    return true;
}


std::vector<DuplicateMatch> DuplicateDetector::findDuplicates(
    const std::vector<FileStats>& allStats) {

    std::vector<DuplicateMatch> duplicates;

    // Compare every pair of files.
    for (size_t i = 0; i < allStats.size(); i++) {

        for (size_t j = i + 1; j < allStats.size(); j++) {

            const auto& linesA = allStats[i].codeLines;
            const auto& linesB = allStats[j].codeLines;

            // Compare every starting position in file A.
            for (size_t a = 0; a < linesA.size(); a++) {

                if (!isMeaningfulCodeLine(linesA[a])) {
                    continue;
                }

                // Compare against every starting position in file B.
                for (size_t b = 0; b < linesB.size(); b++) {

                    if (!isMeaningfulCodeLine(linesB[b])) {
                        continue;
                    }

                    // Check whether the current lines match.
                    if (linesA[a] != linesB[b]) {
                        continue;
                    }

                    // We found the beginning of a possible duplicate block.
                    std::vector<std::string> matchingLines;

                    size_t offset = 0;

                    while (
                        a + offset < linesA.size() &&
                        b + offset < linesB.size() &&
                        linesA[a + offset] == linesB[b + offset] &&
                        isMeaningfulCodeLine(linesA[a + offset])
                    ) {

                        matchingLines.push_back(linesA[a + offset]);
                        offset++;
                    }

                    // Only report blocks containing at least 2 lines.
                    if (matchingLines.size() >= 2) {

                        DuplicateMatch match;

                        match.firstFile = allStats[i].filePath;
                        match.secondFile = allStats[j].filePath;
                        match.codeLines = matchingLines;

                        duplicates.push_back(match);

                        // Skip ahead to avoid repeatedly finding
                        // the same block from the same starting point.
                        a += matchingLines.size() - 1;

                        break;
                    }
                }
            }
        }
    }

    return duplicates;
}