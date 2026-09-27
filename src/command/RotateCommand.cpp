#include <command/RotateCommand.hpp>

#include <Scene.hpp>
#include <validation/Validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

RotateCommand::RotateCommand(RotationArgs args)
    : args_(args) {
    require_validation(rotationSchema, args_);
}

void RotateCommand::execute(Scene& scene) const {
    scene.rotate(args_);
}