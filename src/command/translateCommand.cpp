#include <command/translateCommand.hpp>

#include <scene.hpp>
#include <validation/validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

translateCommand::translateCommand(vector2D offset)
    : offset_(offset) {
    require_validation_t(vectorSchema, offset_);
}

void translateCommand::execute(scene& scene) const {
    scene.translate(offset_);
}