#ifndef CIRCLE_COMMAND_HPP
#define CIRCLE_COMMAND_HPP

#include <command/ICommand.hpp>
#include <validation/Validation.hpp>
#include <Scene.hpp>
#include <validation/schema/geometrySchemas.hpp>
#include <shape/Circle.hpp>


class DrawCircleCommand final : public ICommand {
public: 
    explicit DrawCircleCommand(const Circle& args) : args_(args) {
        require_validation(circleSchema,
            CircleArgs{ args_.center(), args.radius() });
    }

    void execute(Scene& scene) const override {
        scene.add(std::make_unique<Circle>(args_));
    }

private:
    const Circle args_;
};

#endif