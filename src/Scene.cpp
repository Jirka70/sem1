#include <Scene.hpp>
#include <validation/schema/geometrySchemas.hpp>

using Transformation = std::function<std::unique_ptr<IShape>(const IShape&)>;

template<typename Transformation>
Shapes transformShapes(
    const Shapes& shapes,
    const Transformation& transformation
) {
    Shapes result;
    result.reserve(shapes.size());

    for (const auto& shape : shapes) {
        result.push_back(transformation(*shape));
    }

    return result;
}

void Scene::translate(Vector2D offset) {
    require_validation(vectorSchema, offset);

    auto transformed = transformShapes(
        shapes_,
        [offset](const IShape& shape) {
            return shape + offset;
        }
    );

    shapes_.swap(transformed);
}

void Scene::rotate(RotationArgs args) {
    const Rotation rotation{args};

    auto transformed = transformShapes(
        shapes_,
        [&rotation](const IShape& shape) {
            return shape.rotate(rotation);
        }
    );

    shapes_.swap(transformed);
}

void Scene::scale(ScaleArgs args) {
    require_validation(scaleSchema, args);

    const Vector2D factors{
        args.factor,
        args.factor
    };

    auto transformed = transformShapes(
        shapes_,
        [center = args.center, factors](const IShape& shape) {
            auto shifted = shape - center;
            auto scaled = *shifted * factors;

            return *scaled + center;
        }
    );

    shapes_.swap(transformed);
}

void Scene::add(std::unique_ptr<IShape> shape) {
    if (!shape) {
        throw std::invalid_argument{"Do sceny nelze pridat prazdny ukazatel"};
    }

    shapes_.push_back(std::move(shape));
}

const std::vector<std::unique_ptr<IShape>>& Scene::shapes() const noexcept {
    return shapes_;
}