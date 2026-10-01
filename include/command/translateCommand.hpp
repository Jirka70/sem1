#ifndef SEM1_COMMAND_TRANSLATE_COMMAND_HPP
#define SEM1_COMMAND_TRANSLATE_COMMAND_HPP

#include <command/iCommand.hpp>
#include <shape/shapeArgs.hpp>

class TranslateCommand final : public ICommand {
public:
    explicit TranslateCommand(Vector2D offset);

    void execute(Scene& scene) const override;

private:
    Vector2D offset_;
};

#endif
