#ifndef SEM1_COMMAND_DRAW_LINE_COMMAND_HPP
#define SEM1_COMMAND_DRAW_LINE_COMMAND_HPP

#include <scene.hpp>
#include <command/iCommand.hpp>
#include <validation/validation.hpp>
#include <shape/line.hpp>

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