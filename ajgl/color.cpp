#include "color.h"

Color::Color()
{
    red = 0;
    blue = 0;
    green = 0;
    alpha = 1;
}

Color::Color(float r, float b, float g, float a)
{
    red = r;
    blue = b;
    green = g;
    alpha = a;
}
