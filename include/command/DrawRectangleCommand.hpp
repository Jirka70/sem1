#ifndef DRAW_RECTANGLE_COMMAND_HPP
#define DRAW_RECTANGLE_COMMAND_HPP

#include <Scene.hpp>
#include <command/ICommand.hpp>
#include <shape/Shape.hpp>
#include <validation/Validation.hpp>

class DrawRectangleCommand final : public ICommand {
public:
    explicit DrawRectangleCommand(const Rectangle args)
        : args_(args) {
        require_validation(rectangleSchema, args_);
    }

    void execute(Scene& scene) const override {
        scene.add(args_);
    }

private:
    const Rectangle args_;
};

#endif