#ifndef DRAWING_ICOMMAND_HPP
#define DRAWING_ICOMMAND_HPP

#include <Scene.hpp>

class ICommand {
public:    
    virtual ~ICommand() = default;
    virtual void execute(Scene& scene) const = 0;
};

#endif