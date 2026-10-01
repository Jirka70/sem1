#ifndef SEM1_SCENE_HPP
#define SEM1_SCENE_HPP

#include <iostream>
#include <vector>
#include "shape/iShape.hpp"
#include "shape/shapeArgs.hpp"

using shapesType = std::vector<std::unique_ptr<iShape>>;

class scene {
public:
    void add(std::unique_ptr<iShape> shape);
    void translate(vector2D offset);
    void rotate(rotationArgs args);
    void scale(scaleArgs args);

    const std::vector<std::unique_ptr<iShape>>& shapes() const noexcept;

private:
    shapesType shapes_;
};

#endif
