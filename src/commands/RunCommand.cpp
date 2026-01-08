#include "../../include/cman/commands/RunCommand.hpp"
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <regex>

namespace fs = std::filesystem;

namespace cman {

void RunCommand::execute(const std::vector<std::string>& args) {
    // Try to determine project name from CMakeLists.txt to guess executable name
    std::string projectName;
    std::ifstream cmake("CMakeLists.txt");
    if (cmake.is_open()) {
        std::string line;
        std::regex projectRegex(R"(project\s*\(\s*(\w+))");
        std::smatch match;
        while (std::getline(cmake, line)) {
            if (std::regex_search(line, match, projectRegex)) {
                projectName = match[1];
                break;
            }
        }
    }

    if (projectName.empty()) {
        throw std::runtime_error("Could not determine project name from CMakeLists.txt");
    }

    // Windows usually puts it in Debug/Release
    // Also handling potential extension-less binaries for cross-platform (though OS is Windows)
    std::vector<fs::path> paths = {
        fs::path("build") / "Debug" / (projectName + ".exe"),
        fs::path("build") / "Release" / (projectName + ".exe"),
        fs::path("build") / (projectName + ".exe"),
        fs::path("build") / projectName
    };

    for (const auto& path : paths) {
        if (fs::exists(path)) {
            std::cout << "Running " << path.string() << "...\n";
            std::string cmd = "\"" + path.string() + "\"";
            // Pass arguments to the executable
            for (const auto& arg : args) {
                cmd += " " + arg;
            }
            std::system(cmd.c_str());
            return;
        }
    }
    
    throw std::runtime_error("Executable not found. Did you build the project?");
}

}
