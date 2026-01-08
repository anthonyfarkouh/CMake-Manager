#pragma once
#include "../Command.hpp"

namespace cman {

class InitCommand : public Command {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string getDescription() const override { return "Initialize a new CMake project"; }
    std::string getName() const override { return "init"; }
};

}
