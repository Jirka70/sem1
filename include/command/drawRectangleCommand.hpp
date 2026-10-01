#ifndef SEM1_COMMAND_DRAW_RECTANGLE_COMMAND_HPP
#define SEM1_COMMAND_DRAW_RECTANGLE_COMMAND_HPP

#include <scene.hpp>
#include <command/iCommand.hpp>
#include <validation/validation.hpp>
#include <shape/rectangle.hpp>

class drawRectangleCommand final : public iCommand {
public:
    explicit drawRectangleCommand(const rectangle& args) : args_(args) {}

    void execute(scene& scene) const override {
        scene.add(std::make_unique<rectangle>(args_));
    }

private:
    const rectangle args_;
};

#endif