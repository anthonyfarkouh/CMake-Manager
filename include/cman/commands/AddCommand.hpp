#pragma once
#include "../Command.hpp"

namespace cman {

class AddCommand : public Command {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string getDescription() const override { return "Add a file to the project"; }
    std::string getName() const override { return "add"; }
};

}