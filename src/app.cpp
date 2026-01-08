#include "../include/cman/app.hpp"
#include "../include/cman/commands/InitCommand.hpp"
#include "../include/cman/commands/BuildCommand.hpp"
#include "../include/cman/commands/RunCommand.hpp"
#include "../include/cman/commands/AddCommand.hpp"
#include <iostream>
#include <vector>

namespace cman {

App::App() {
    registerCommand(std::make_unique<InitCommand>());
    registerCommand(std::make_unique<BuildCommand>());
    registerCommand(std::make_unique<RunCommand>());
    registerCommand(std::make_unique<AddCommand>());
}

void App::registerCommand(std::unique_ptr<Command> cmd) {
    commands[cmd->getName()] = std::move(cmd);
}

int App::run(int argc, char* args[]) {
    if (argc < 2) {
        std::cout << "Usage: cman <command> [options]\n";
        std::cout << "Available commands:\n";
        for (const auto& pair : commands) {
            std::cout << "  " << pair.first << ": " << pair.second->getDescription() << "\n";
        }
        return 1;
    }

    std::string commandName = args[1];
    auto it = commands.find(commandName);
    if (it != commands.end()) {
        std::vector<std::string> cmdArgs;
        for (int i = 2; i < argc; ++i) {
            cmdArgs.push_back(args[i]);
        }
        try {
            it->second->execute(cmdArgs);
            return 0;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    } else {
        std::cerr << "Unknown command: " << commandName << "\n";
        return 1;
    }
}

}
