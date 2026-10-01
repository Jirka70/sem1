#ifndef SEM1_COMMAND_ROTATE_COMMAND_HPP
#define SEM1_COMMAND_ROTATE_COMMAND_HPP

#include <command/iCommand.hpp>
#include <shape/shapeArgs.hpp>

class rotateCommand final : public iCommand {
public:
    explicit rotateCommand(rotationArgs args);

    void execute(scene& scene) const override;

private:
    rotationArgs args_;
};

#endif
