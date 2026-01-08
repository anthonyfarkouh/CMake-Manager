#include "../../include/cman/commands/InitCommand.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace cman {

void InitCommand::execute(const std::vector<std::string>& args) {
    if (fs::exists("CMakeLists.txt")) {
        std::cout << "CMakeLists.txt already exists.\n";
        return;
    }

    std::string projectName = "MyProject";
    if (!args.empty()) {
        projectName = args[0];
    } else {
        std::cout << "Enter project name (default: MyProject): ";
        std::string input;
        if (std::getline(std::cin, input) && !input.empty()) {
            projectName = input;
        }
    }

    std::ofstream cmake("CMakeLists.txt");
    cmake << "cmake_minimum_required(VERSION 3.10)\n";
    cmake << "project(" << projectName << ")\n\n";
    cmake << "set(CMAKE_CXX_STANDARD 17)\n";
    cmake << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n";
    cmake << "add_executable(" << projectName << " src/main.cpp)\n";
    cmake.close();

    std::cout << "Created CMakeLists.txt\n";

    if (!fs::exists("src")) {
        fs::create_directory("src");
    }

    if (!fs::exists("src/main.cpp")) {
        std::ofstream main("src/main.cpp");
        main << "#include <iostream>\n\n";
        main << "int main() {\n";
        main << "    std::cout << \"Hello from " << projectName << "!\" << std::endl;\n";
        main << "    return 0;\n";
        main << "}\n";
        main.close();
        std::cout << "Created src/main.cpp\n";
    }
}

}
