#ifndef SEM1_COMMAND_I_COMMAND_HPP
#define SEM1_COMMAND_I_COMMAND_HPP

#include <scene.hpp>

class ICommand {
public:    
    virtual ~ICommand() = default;
    virtual void execute(Scene& scene) const = 0;
};

#endif