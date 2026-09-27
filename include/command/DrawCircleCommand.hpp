#ifndef CIRCLE_COMMAND_HPP
#define CIRCLE_COMMAND_HPP

#include <command/ICommand.hpp>
#include <validation/Validation.hpp>
#include <Scene.hpp>
#include <validation/schema/shape/circleSchema.hpp>


class DrawCircleCommand final : public ICommand {
public: 
    explicit DrawCircleCommand(const Circle args) : args_(args) {
        require_validation(circleSchema, args_);
    }

    void execute(Scene& scene) const override {
        scene.add(args_);
    }

private:
    const Circle args_;
};

#endif