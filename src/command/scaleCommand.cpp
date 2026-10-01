#include <command/scaleCommand.hpp>

#include <scene.hpp>
#include <validation/validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

ScaleCommand::ScaleCommand(ScaleArgs args)
    : args_(args) {
    require_validation_t(scaleSchema, args_);
}

void ScaleCommand::execute(Scene& scene) const {
    scene.scale(args_);
}