#ifndef GEOMETRY_SCHEMAS_HPP
#define GEOMETRY_SCHEMAS_HPP

#include <shape/ShapeArgs.hpp>
#include <validation/Validation.hpp>

extern const Schema<Vector2D> vectorSchema;
extern const Schema<Vector2D> scaleFactorsSchema;

extern const Schema<CircleArgs> circleSchema;
extern const Schema<LineArgs> lineSchema;
extern const Schema<RectangleArgs> rectangleSchema;

extern const Schema<RotationArgs> rotationSchema;
extern const Schema<ScaleArgs> scaleSchema;

#endif