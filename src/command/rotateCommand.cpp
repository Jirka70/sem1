#include <command/rotateCommand.hpp>

#include <scene.hpp>
#include <validation/validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

rotateCommand::rotateCommand(rotationArgs args)
    : args_(args) {
    require_validation_t(rotationSchema, args_);
}

void rotateCommand::execute(scene& scene) const {
    scene.rotate(args_);
}