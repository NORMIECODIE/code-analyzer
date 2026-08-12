#include "DuplicateDetector.h"

// Check whether a line is meaningful enough to report as duplicate code.
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

    for (size_t i = 0; i < allStats.size(); i++) {

        for (size_t j = i + 1; j < allStats.size(); j++) {

            for (const auto& lineA : allStats[i].codeLines) {

                // Ignore meaningless lines.
                if (!isMeaningfulCodeLine(lineA)) {
                    continue;
                }

                for (const auto& lineB : allStats[j].codeLines) {

                    if (lineA == lineB &&
                        isMeaningfulCodeLine(lineB)) {

                        DuplicateMatch match;

                        match.firstFile = allStats[i].filePath;
                        match.secondFile = allStats[j].filePath;
                        match.code = lineA;

                        duplicates.push_back(match);

                        // We found this line in the second file.
                        break;
                    }
                }
            }
        }
    }

    return duplicates;
}