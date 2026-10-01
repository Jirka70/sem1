#ifndef SEM1_VALIDATION_SCHEMA_GEOMETRY_SCHEMAS_HPP
#define SEM1_VALIDATION_SCHEMA_GEOMETRY_SCHEMAS_HPP

#include <shape/shapeArgs.hpp>
#include <validation/validation.hpp>

extern const schema<Vector2D> vectorSchema;
extern const schema<Vector2D> scaleFactorsSchema;

extern const schema<CircleArgs> circleSchema;
extern const schema<LineArgs> lineSchema;
extern const schema<RectangleArgs> rectangleSchema;

extern const schema<RotationArgs> rotationSchema;
extern const schema<ScaleArgs> scaleSchema;

#endif