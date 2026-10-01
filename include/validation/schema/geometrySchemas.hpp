#ifndef SEM1_VALIDATION_SCHEMA_GEOMETRY_SCHEMAS_HPP
#define SEM1_VALIDATION_SCHEMA_GEOMETRY_SCHEMAS_HPP

#include <shape/shapeArgs.hpp>
#include <validation/validation.hpp>

extern const schema<vector2D> vectorSchema;
extern const schema<vector2D> scaleFactorsSchema;

extern const schema<circleArgs> circleSchema;
extern const schema<lineArgs> lineSchema;
extern const schema<rectangleArgs> rectangleSchema;

extern const schema<rotationArgs> rotationSchema;
extern const schema<scaleArgs> scaleSchema;

#endif