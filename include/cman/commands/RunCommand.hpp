#pragma once
#include "../Command.hpp"

namespace cman {

class RunCommand : public Command {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string getDescription() const override { return "Run the project executable"; }
    std::string getName() const override { return "run"; }
};

}
