#include <scene.hpp>
#include <validation/schema/geometrySchemas.hpp>

using transformationType = std::function<std::unique_ptr<iShape>(const iShape&)>;

template<typename transformationType>
shapesType transform_shapes_t(
    const shapesType& shapes,
    const transformationType& transformation
) {
    shapesType result;
    result.reserve(shapes.size());

    for (const auto& shape : shapes) {
        result.push_back(transformation(*shape));
    }

    return result;
}

void scene::translate(vector2D offset) {
    require_validation_t(vectorSchema, offset);

    auto transformed = transform_shapes_t(
        shapes_,
        [offset](const iShape& shape) {
            return shape + offset;
        }
    );

    shapes_.swap(transformed);
}

void scene::rotate(rotationArgs args) {
    const rotation rotation{args};

    auto transformed = transform_shapes_t(
        shapes_,
        [&rotation](const iShape& shape) {
            return shape.rotate(rotation);
        }
    );

    shapes_.swap(transformed);
}

void scene::scale(scaleArgs args) {
    require_validation_t(scaleSchema, args);

    const vector2D factors{
        args.factor,
        args.factor
    };

    if (args.factor == 1.0) {
        return;
    }

    auto transformed = transform_shapes_t(
        shapes_,
        [center = args.center, factors](const iShape& shape) {
            auto shifted = shape - center;
            auto scaled = *shifted * factors;

            return *scaled + center;
        }
    );

    shapes_.swap(transformed);
}

void scene::add(std::unique_ptr<iShape> shape) {
    if (!shape) {
        throw std::invalid_argument{"Do sceny nelze pridat prazdny ukazatel"};
    }

    shapes_.push_back(std::move(shape));
}

const std::vector<std::unique_ptr<iShape>>& scene::shapes() const noexcept {
    return shapes_;
}