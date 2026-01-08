#pragma once
#include <string>
#include <memory>
#include <map>
#include "Command.hpp"

namespace cman {

class App {
public:
    App();
    int run(int argc, char* args[]);

private:
    void registerCommand(std::unique_ptr<Command> cmd);
    std::map<std::string, std::unique_ptr<Command>> commands;
};

}
