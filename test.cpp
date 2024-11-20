#include "tui.h"
#include "geometry.h"
#include <iostream>

int main()
{
    al_init();
    One_line_text::font(al_create_builtin_font());
    One_line_text one_line_text = One_line_text(Vector(0, 0), "hello");
    std::cout << one_line_text.text();
    return 0;
}