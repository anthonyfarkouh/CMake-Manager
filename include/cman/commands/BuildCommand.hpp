#pragma once
#include "../Command.hpp"

namespace cman {

class BuildCommand : public Command {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string getDescription() const override { return "Build the project"; }
    std::string getName() const override { return "build"; }
};

}
