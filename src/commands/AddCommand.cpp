#include "../../include/cman/commands/AddCommand.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

namespace cman {

void AddCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        throw std::runtime_error("Usage: cman add <filename>");
    }

    std::string filename = args[0];
    fs::path filepath = filename;
    
    // Create directory if it doesn't exist
    if (filepath.has_parent_path()) {
        fs::create_directories(filepath.parent_path());
    }

    if (!fs::exists(filepath)) {
        std::ofstream file(filepath);
        file << "#include <iostream>\n\n";
        file << "// TODO: Implement functionality for " << filepath.filename().string() << "\n";
        file.close();
        std::cout << "Created file: " << filename << "\n";
    } else {
        std::cout << "File already exists: " << filename << "\n";
    }

    // Update CMakeLists.txt
    std::ifstream cmakeIn("CMakeLists.txt");
    if (!cmakeIn.is_open()) {
        throw std::runtime_error("CMakeLists.txt not found.");
    }

    std::string content((std::istreambuf_iterator<char>(cmakeIn)), std::istreambuf_iterator<char>());
    cmakeIn.close();

    // Regex to find add_executable
    // add_executable(ProjectName src/main.cpp src/other.cpp)
    // Note: This regex is simple and might not handle all CMake formatting nuances (like newlines) but should work for the InitCommand created file.
    std::regex addExecRegex(R"(add_executable\s*\(\s*(\w+)\s+([^)]+)\))");
    std::smatch match;
    
    if (std::regex_search(content, match, addExecRegex)) {
        std::string currentSources = match[2];
        // Check if file is already linked
        if (currentSources.find(filename) == std::string::npos) {
             // We just append to the end of the sources list
            // However, the regex group [^)]+ captures everything up to the closing paren
            // We need to be careful with formatting.
            
            std::string prefix = match.str().substr(0, match.position(2) - match.position(0));
            // match[0] is the whole string "add_executable(...)"
            // match[1] is ProjectName
            // match[2] is sources
            
            std::string newBlock = "add_executable(" + std::string(match[1]) + " " + std::string(match[2]) + " " + filename + ")";
            
            // Allow for multi-line support in regex for future improvement, but for now simple replacement
            content.replace(match.position(0), match.length(0), newBlock);
            
            std::ofstream cmakeOut("CMakeLists.txt");
            cmakeOut << content;
            std::cout << "Added " << filename << " to CMakeLists.txt\n";
        } else {
            std::cout << "File is already in CMakeLists.txt\n";
        }
    } else {
        std::cout << "Could not find valid add_executable directive in CMakeLists.txt to update.\n";
    }
}

}