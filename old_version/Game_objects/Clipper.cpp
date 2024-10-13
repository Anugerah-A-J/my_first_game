#include "Clipper.h"
#include <allegro5/allegro_primitives.h>

void Clipper::draw() const
{
    al_draw_filled_rectangle(
        left_clipper.get_origin().get_x(),
        left_clipper.get_origin().get_y(),
        left_clipper.get_max().get_x(),
        left_clipper.get_max().get_y(),
        color
    );

    al_draw_filled_rectangle(
        top_clipper.get_origin().get_x(),
        top_clipper.get_origin().get_y(),
        top_clipper.get_max().get_x(),
        top_clipper.get_max().get_y(),
        color
    );

    al_draw_filled_rectangle(
        right_clipper.get_origin().get_x(),
        right_clipper.get_origin().get_y(),
        right_clipper.get_max().get_x(),
        right_clipper.get_max().get_y(),
        color
    );

    al_draw_filled_rectangle(
        bottom_clipper.get_origin().get_x(),
        bottom_clipper.get_origin().get_y(),
        bottom_clipper.get_max().get_x(),
        bottom_clipper.get_max().get_y(),
        color
    );
}