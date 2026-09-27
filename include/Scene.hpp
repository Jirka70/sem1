#ifndef SCENE_HPP
#define SCENE_HPP

#include <shape/Shape.hpp>
#include <iostream>
#include <vector>

class Scene {
public:
    void add(const Shape& shape);
    const std::vector<Shape>& shapes() const noexcept;

private:
    std::vector<Shape> shapes_;
};

#endif
