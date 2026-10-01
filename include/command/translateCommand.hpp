#ifndef SEM1_COMMAND_TRANSLATE_COMMAND_HPP
#define SEM1_COMMAND_TRANSLATE_COMMAND_HPP

#include <command/iCommand.hpp>
#include <shape/shapeArgs.hpp>

class translateCommand final : public iCommand {
public:
    explicit translateCommand(vector2D offset);

    void execute(scene& scene) const override;

private:
    vector2D offset_;
};

#endif
