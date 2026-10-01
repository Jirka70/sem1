#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <vector>
#include "shape/IShape.hpp"
#include "shape/ShapeArgs.hpp"

using Shapes = std::vector<std::unique_ptr<IShape>>;

class Scene {
public:
    void add(std::unique_ptr<IShape> shape);
    void translate(Vector2D offset);
    void rotate(RotationArgs args);
    void scale(ScaleArgs args);

    const std::vector<std::unique_ptr<IShape>>& shapes() const noexcept;

private:
    Shapes shapes_;
};

#endif
