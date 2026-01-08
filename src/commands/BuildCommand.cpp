#include "../../include/cman/commands/BuildCommand.hpp"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

namespace cman {

void BuildCommand::execute(const std::vector<std::string>& args) {
    std::cout << "Configuring CMake...\n";
    int ret = std::system("cmake -S . -B build");
    if (ret != 0) {
        throw std::runtime_error("CMake configuration failed.");
    }

    std::cout << "Building project...\n";
    ret = std::system("cmake --build build");
    if (ret != 0) {
        throw std::runtime_error("Build failed.");
    }
}

}
