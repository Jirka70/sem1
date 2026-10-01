#include <command/translateCommand.hpp>

#include <scene.hpp>
#include <validation/validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

TranslateCommand::TranslateCommand(Vector2D offset)
    : offset_(offset) {
    require_validation_t(vectorSchema, offset_);
}

void TranslateCommand::execute(Scene& scene) const {
    scene.translate(offset_);
}