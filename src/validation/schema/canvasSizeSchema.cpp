#include <validation/schema/canvasSizeSchema.hpp>

const schema<CanvasSize> canvasSizeSchema{
    {
        "width",
        "Sirka platna musi byt vetsi nez nula",
        [](const CanvasSize& size) {
            return size.width > 0;
        }
    },
    {
        "height",
        "Vyska platna musi byt vetsi nez nula",
        [](const CanvasSize& size) {
            return size.height > 0;
        }
    }
};