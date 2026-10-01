#ifndef SEM1_COMMAND_DRAW_CIRCLE_COMMAND_HPP
#define SEM1_COMMAND_DRAW_CIRCLE_COMMAND_HPP

#include <command/iCommand.hpp>
#include <validation/validation.hpp>
#include <scene.hpp>
#include <validation/schema/geometrySchemas.hpp>
#include <shape/circle.hpp>


class drawCircleCommand final : public iCommand {
public: 
    explicit drawCircleCommand(const circle& args) : args_(args) {}

    void execute(scene& scene) const override {
        scene.add(std::make_unique<circle>(args_));
    }

private:
    const circle args_;
};

#endif