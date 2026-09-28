#ifndef TRANSLATE_COMMAND_HPP
#define TRANSLATE_COMMAND_HPP

#include <command/ICommand.hpp>
#include <shape/ShapeArgs.hpp>

class TranslateCommand final : public ICommand {
public:
    explicit TranslateCommand(Vector2D offset);

    void execute(Scene& scene) const override;

private:
    Vector2D offset_;
};

#endif
