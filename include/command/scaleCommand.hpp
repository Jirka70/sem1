#ifndef SEM1_COMMAND_SCALE_COMMAND_HPP
#define SEM1_COMMAND_SCALE_COMMAND_HPP

#include <command/iCommand.hpp>
#include <shape/shapeArgs.hpp>

class scaleCommand final : public iCommand {
public:
    explicit scaleCommand(scaleArgs args);

    void execute(scene& scene) const override;

private:
    scaleArgs args_;
};

#endif