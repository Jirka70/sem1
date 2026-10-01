#include <validation/schema/canvasSizeSchema.hpp>

const schema<canvasSize> canvasSizeSchema{
    {
        "width",
        "Sirka platna musi byt vetsi nez nula",
        [](const canvasSize& size) {
            return size.width > 0;
        }
    },
    {
        "height",
        "Vyska platna musi byt vetsi nez nula",
        [](const canvasSize& size) {
            return size.height > 0;
        }
    }
};