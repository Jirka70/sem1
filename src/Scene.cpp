#include <Scene.hpp>

void Scene::add(const Shape& shape) {
    shapes_.push_back(shape);
}

const std::vector<Shape>& Scene::shapes() const noexcept {
    return shapes_;
}