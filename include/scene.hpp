#ifndef SEM1_SCENE_HPP
#define SEM1_SCENE_HPP

#include <iostream>
#include <vector>
#include "shape/iShape.hpp"
#include "shape/shapeArgs.hpp"

using shapesType = std::vector<std::unique_ptr<IShape>>;

class Scene {
public:
    void add(std::unique_ptr<IShape> shape);
    void translate(Vector2D offset);
    void rotate(RotationArgs args);
    void scale(ScaleArgs args);

    const std::vector<std::unique_ptr<IShape>>& shapes() const noexcept;

private:
    shapesType shapes_;
};

#endif
