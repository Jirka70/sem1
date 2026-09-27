#ifndef SCALE_COMMAND_HPP
#define SCALE_COMMAND_HPP

#include <command/ICommand.hpp>
#include <shape/ShapeArgs.hpp>

class ScaleCommand final : public ICommand {
public:
    explicit ScaleCommand(ScaleArgs args);

    void execute(Scene& scene) const override;

private:
    ScaleArgs args_;
};

#endif