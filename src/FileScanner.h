#pragma once
#include <string>
#include <vector>

// Recursively finds all C/C++ source files under a given root directory.
class FileScanner {
public:
    explicit FileScanner(const std::string& rootPath);

    // Returns full paths to every .cpp/.h/.hpp/.cc file found.
    std::vector<std::string> findSourceFiles() const;

private:
    std::string rootPath_;
    bool hasSourceExtension(const std::string& path) const;
};
