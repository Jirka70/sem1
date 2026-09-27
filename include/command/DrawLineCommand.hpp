#ifndef DRAW_LINE_COMMAND_HPP
#define DRAW_LINE_COMMAND_HPP

#include <Scene.hpp>
#include <command/ICommand.hpp>
#include <shape/Shape.hpp>
#include <validation/Validation.hpp>

class DrawLineCommand final : public ICommand {
public:
    explicit DrawLineCommand(const Line args)
        : args_(args) {
        require_validation(lineSchema, args_);
    }

    void execute(Scene& scene) const override {
        scene.add(args_);
    }

private:
    const Line args_;
};

#endif