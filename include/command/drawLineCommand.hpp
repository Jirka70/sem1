#ifndef SEM1_COMMAND_DRAW_LINE_COMMAND_HPP
#define SEM1_COMMAND_DRAW_LINE_COMMAND_HPP

#include <scene.hpp>
#include <command/iCommand.hpp>
#include <validation/validation.hpp>
#include <shape/line.hpp>

class drawLineCommand final : public iCommand {
public:
    explicit drawLineCommand(const line& args) : args_(args) {}
 
    void execute(scene& scene) const override {
        scene.add(std::make_unique<line>(args_));
    }

private:
    const line args_;
};

#endif