#include <command/ScaleCommand.hpp>

#include <Scene.hpp>
#include <validation/Validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

ScaleCommand::ScaleCommand(ScaleArgs args)
    : args_(args) {
    require_validation(scaleSchema, args_);
}

void ScaleCommand::execute(Scene& scene) const {
    scene.scale(args_);
}