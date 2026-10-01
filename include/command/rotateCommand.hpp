#ifndef SEM1_COMMAND_ROTATE_COMMAND_HPP
#define SEM1_COMMAND_ROTATE_COMMAND_HPP

#include <command/iCommand.hpp>
#include <shape/shapeArgs.hpp>

class RotateCommand final : public ICommand {
public:
    explicit RotateCommand(RotationArgs args);

    void execute(Scene& scene) const override;

private:
    RotationArgs args_;
};

#endif
