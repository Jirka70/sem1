#include <command/scaleCommand.hpp>

#include <scene.hpp>
#include <validation/validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

scaleCommand::scaleCommand(scaleArgs args)
    : args_(args) {
    require_validation_t(scaleSchema, args_);
}

void scaleCommand::execute(scene& scene) const {
    scene.scale(args_);
}