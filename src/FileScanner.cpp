#include "FileScanner.h"
#include <filesystem>

namespace fs = std::filesystem;

FileScanner::FileScanner(const std::string& rootPath) : rootPath_(rootPath) {}

bool FileScanner::hasSourceExtension(const std::string& path) const {
    static const std::vector<std::string> extensions = {".cpp", ".h", ".hpp", ".cc"};
    for (const auto& ext : extensions) {
        if (path.size() >= ext.size() &&
            path.compare(path.size() - ext.size(), ext.size(), ext) == 0) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> FileScanner::findSourceFiles() const {
    std::vector<std::string> results;

    for (const auto& entry : fs::recursive_directory_iterator(rootPath_)) {
        if (entry.is_regular_file() && hasSourceExtension(entry.path().string())) {
            results.push_back(entry.path().string());
        }
    }

    return results;
}
