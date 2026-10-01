#ifndef SEM1_COMMAND_SCALE_COMMAND_HPP
#define SEM1_COMMAND_SCALE_COMMAND_HPP

#include <command/iCommand.hpp>
#include <shape/shapeArgs.hpp>

class ScaleCommand final : public ICommand {
public:
    explicit ScaleCommand(ScaleArgs args);

    void execute(Scene& scene) const override;

private:
    ScaleArgs args_;
};

#endif