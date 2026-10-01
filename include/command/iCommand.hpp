#ifndef SEM1_COMMAND_I_COMMAND_HPP
#define SEM1_COMMAND_I_COMMAND_HPP

#include <scene.hpp>

class iCommand {
public:    
    virtual ~iCommand() = default;
    virtual void execute(scene& scene) const = 0;
};

#endif