#ifndef ROTATE_COMMAND_HPP
#define ROTATE_COMMAND_HPP

#include <command/ICommand.hpp>
#include <shape/ShapeArgs.hpp>

class RotateCommand final : public ICommand {
public:
    RotateCommand(RotationArgs args);

    void execute(Scene& scene) const override;

private:
    RotationArgs args_;
};

#endif