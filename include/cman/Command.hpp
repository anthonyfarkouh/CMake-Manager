#pragma once
#include <string>
#include <vector>

namespace cman {

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(const std::vector<std::string>& args) = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getName() const = 0;
};

}
