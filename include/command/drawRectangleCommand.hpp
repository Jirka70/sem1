#ifndef SEM1_COMMAND_DRAW_RECTANGLE_COMMAND_HPP
#define SEM1_COMMAND_DRAW_RECTANGLE_COMMAND_HPP

#include <scene.hpp>
#include <command/iCommand.hpp>
#include <validation/validation.hpp>
#include <shape/rectangle.hpp>

class DrawRectangleCommand final : public ICommand {
public:
    explicit DrawRectangleCommand(const Rectangle& args) : args_(args) {}

    void execute(Scene& scene) const override {
        scene.add(std::make_unique<Rectangle>(args_));
    }

private:
    const Rectangle args_;
};

#endif