#include <command/rotateCommand.hpp>

#include <scene.hpp>
#include <validation/validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

RotateCommand::RotateCommand(RotationArgs args)
    : args_(args) {
    require_validation_t(rotationSchema, args_);
}

void RotateCommand::execute(Scene& scene) const {
    scene.rotate(args_);
}