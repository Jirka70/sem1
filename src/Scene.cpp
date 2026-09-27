#include <Scene.hpp>

void Scene::add(std::unique_ptr<IShape> shape) {
    shapes_.push_back(std::move(shape));
}

const std::vector<std::unique_ptr<IShape>>& Scene::shapes() const noexcept {
    return shapes_;
}