#ifndef DRAW_RECTANGLE_COMMAND_HPP
#define DRAW_RECTANGLE_COMMAND_HPP

#include <Scene.hpp>
#include <command/ICommand.hpp>
#include <validation/Validation.hpp>
#include <shape/Rectangle.hpp>

class DrawRectangleCommand final : public ICommand {
public:
    explicit DrawRectangleCommand(const Rectangle& args)
        : args_(args) {
        require_validation(rectangleSchema, RectangleArgs{args.corners()});
    }

    void execute(Scene& scene) const override {
        scene.add(std::make_unique<Rectangle>(args_));
    }

private:
    const Rectangle args_;
};

#endif