#include "color.h"

Color::Color()
{
    r = 0;
    b = 0;
    g = 0;
    a = 1;
}

Color::Color(float red, float blue, float green, float alpha)
{

    r = red;
    b = blue;
    g = green;
    a = alpha;
}
