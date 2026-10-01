#ifndef SEM1_COMMAND_DRAW_CIRCLE_COMMAND_HPP
#define SEM1_COMMAND_DRAW_CIRCLE_COMMAND_HPP

#include <command/iCommand.hpp>
#include <validation/validation.hpp>
#include <scene.hpp>
#include <validation/schema/geometrySchemas.hpp>
#include <shape/circle.hpp>


class DrawCircleCommand final : public ICommand {
public: 
    explicit DrawCircleCommand(const Circle& args) : args_(args) {}

    void execute(Scene& scene) const override {
        scene.add(std::make_unique<Circle>(args_));
    }

private:
    const Circle args_;
};

#endif