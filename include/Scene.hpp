#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <vector>
#include "shape/IShape.hpp"

class Scene {
public:
    void add(std::unique_ptr<IShape> shape);
    const std::vector<std::unique_ptr<IShape>>& shapes() const noexcept;

private:
    std::vector<std::unique_ptr<IShape>> shapes_;
};

#endif
