#ifndef DRAW_LINE_COMMAND_HPP
#define DRAW_LINE_COMMAND_HPP

#include <Scene.hpp>
#include <command/ICommand.hpp>
#include <validation/Validation.hpp>
#include <shape/Line.hpp>

class DrawLineCommand final : public ICommand {
public:
    explicit DrawLineCommand(const Line& args) : args_(args) {}

    void execute(Scene& scene) const override {
        scene.add(std::make_unique<Line>(args_));
    }

private:
    const Line args_;
};

#endif