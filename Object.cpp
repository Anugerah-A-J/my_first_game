#include "Object.hpp"
#include "Param.hpp"
#include "Shape.hpp"

Aim::Aim()
: 
    reach_circle{Vector(0, 0), Param::reach_radius},
    end_point{0, 0},
    direction_sign{Vector(0, 0), Vector(0, 0), Vector(0, 0)},
    color{Param::magenta},
    line_width{Param::line_width},
    reach_circle_is_visible{false},
    direction_sign_is_visible{false}
{}

void Aim::Draw() const
{
    if (reach_circle_is_visible)
        reach_circle.Draw(color, line_width);

    if (direction_sign_is_visible) {
        direction_sign.Draw(color, line_width);
        // Line(reach_circle.Center(), pawn_destination).Draw(color, line_width);
    }
}

void Aim::Center(const Vector& point)
{
    reach_circle.Center(point);
}

const Vector& Aim::Center()
{
    return reach_circle.Center();
}

const Vector& Aim::End_point() const
{
    return end_point;
}

void Aim::Update_direction(const Vector& mouse_coordinate)
{
    Vector unit = (mouse_coordinate - reach_circle.Center()).Unit();

    end_point = reach_circle.Center() - unit * reach_circle.Radius();

    direction_sign.Vertex_1(reach_circle.Center() + unit * Param::unit_length);

    Vector temp = direction_sign.Vertex_1() + unit * Param::unit_length;

    direction_sign.Vertex_2(temp + Matrix(0, 1, -1, 0) * unit * Param::unit_length / Param::sqrt_3);

    direction_sign.Vertex_3(temp + Matrix(0, -1, 1, 0) * unit * Param::unit_length / Param::sqrt_3);
}

void Aim::Show_reach_circle()
{
    reach_circle_is_visible = true;
}

void Aim::Show_direction_sign()
{
    direction_sign_is_visible = true;
}

void Aim::Hide()
{
    reach_circle_is_visible = false;
    direction_sign_is_visible = false;
}

void Aim::Color(const ALLEGRO_COLOR& color)
{
    this->color = color;
}

bool Aim::Reach_circle_is_visible() const
{
    return reach_circle_is_visible;
}

bool Aim::Direction_sign_is_visible() const
{
    return direction_sign_is_visible;
}

Clipper::Clipper(const Rectangle& map_fence_shape)
: 
    left{
        Vector(0, 0),
        Vector((Param::window_width - map_fence_shape.Width()) / 2, Param::window_height)
    },
    top{
        Vector(0, 0),
        Vector(Param::window_width, (Param::window_height - map_fence_shape.Height()) / 2)
    },
    right{
        map_fence_shape.Top_right(),
        Vector(Param::window_width, Param::window_height)
    },
    bottom{
        map_fence_shape.Bottom_left(),
        Vector(Param::window_width, Param::window_height)
    },
    color{Param::black}
{}

void Clipper::Draw() const
{
    left.Draw(color);
    top.Draw(color);
    right.Draw(color);
    bottom.Draw(color);
}

Fence::Fence(const Vector& origin, const Vector& size)
:
    shape{origin, size},
    color{Param::red},
    line_width{Param::line_width}
{}

void Fence::Draw() const
{
    shape.Draw(color, line_width);
}

const Vector& Fence::Origin() const
{
    return shape.Origin();
}

Vector Fence::Top_right() const
{
    return shape.Top_right();
}

Vector Fence::Top_left() const
{
    return shape.Top_left();
}

Vector Fence::Bottom_left() const
{
    return shape.Bottom_left();
}

Vector Fence::Bottom_right() const
{
    return shape.Bottom_right();
}

Vector Fence::Center() const
{
    return shape.Center();
}

float Fence::Width() const
{
    return shape.Width();
}

float Fence::Height() const
{
    return shape.Height();
}

const Rectangle &Fence::Shape() const
{
    return shape;
}

// void Fence::Hurt(Player& player) const
// {
//     float t = Collision::Circle_inside_rectangle(player.Shape(), shape, player.Last_translation());

//     if (t == 2 || Pawn::Vanish_immediately())
//         return;

//     moving_pawn.Retreat(1 - t);
//     moving_pawn.Stop();
//     dying_pawns.insert(&moving_pawn);
// }

Wall::Wall(const Vector& origin, const Vector& size)
:
    shape{origin, size}
{}

void Wall::Draw() const
{
    shape.Draw(Param::yellow);
}

const Rectangle& Wall::Shape() const
{
    return shape;
}

void Wall::Center(const Vector& point)
{
    shape.Center(point);
}

Wall Wall::Mirror_x(const Vector& point) const
{
    Wall temp = *this;
    temp.shape = shape.Mirror_x(point);
    return temp;
}

Wall Wall::Mirror_y(const Vector& point) const
{
    Wall temp = *this;
    temp.shape = shape.Mirror_y(point);
    return temp;
}

// class Tree
// {
// public:
//     Tree(const Vector& center, float overall_diameter)
//     :
//         diameter{overall_diameter},
//         shape{6, Circle(center, overall_diameter / 6)},
//         filler{center, shape.front().Radius() * 1.7321f}
//     {
//         std::array<float, 6> xs{1, 0.5f, -0.5f, -1, -0.5f, 0.5f};
//         std::array<float, 6> ys{0, 0.5f, 0.5f, 0, -0.5f, -0.5f};

//         std::for_each(shape.begin(), shape.end(), [&, i = 0](Circle& c) mutable {
//             c.Translate(
//                 2 * c.Radius() * Vector(xs.at(i), ys.at(i) * Param::sqrt_3)
//             );

//             i++;
//         });
//     }

//     void Draw() const
//     {
//         std::for_each(shape.begin(), shape.end(), [](const Circle& c) { c.Draw(Param::green); });

//         filler.Draw(Param::green);
//     }

//     void Translate(const Vector& displacement)
//     {
//         std::for_each(shape.begin(), shape.end(), [&](Circle& c) { c.Translate(displacement); });

//         filler.Translate(displacement);
//     }

//     Tree Mirror_x(const Vector& point) const
//     {
//         Tree temp = *this;

//         temp.filler = temp.filler.Mirror_x(point);

//         std::transform(temp.shape.begin(), temp.shape.end(), temp.shape.begin(), [&](const Circle& c) 
//         {
//             return c.Mirror_x(point);
//         });

//         return temp;
//     }

//     Tree Mirror_y(const Vector& point) const
//     {
//         Tree temp = *this;

//         temp.filler = temp.filler.Mirror_y(point);

//         std::transform(temp.shape.begin(), temp.shape.end(), temp.shape.begin(), [&](const Circle& c) 
//         {
//             return c.Mirror_y(point);
//         });

//         return temp;
//     }

//     float Min_t(const Pawn& moving_pawn) const
//     {
//         std::vector<float> t;
//         t.reserve(shape.size());

//         for (const Circle& circle : shape)
//             t.push_back(collision::Circle_vs_circle(moving_pawn.Shape(),
//                                                     circle,
//                                                     moving_pawn.Last_translation()));

//         return *std::min_element(t.begin(), t.end());
//     }

// private:
//     float diameter;
//     std::vector<Circle> shape;
//     Circle filler;
// };

// class X
// {
// public:
//     X(const Vector& origin, float size)
//     :
//         size{size},
//         shape{
//             Line(origin, origin + Vector(size, size)),
//             Line(origin, origin + Vector(size, size)).Mirror_x(origin + Vector(size, size) / 2)
//         }
//     {}

//     void Draw() const
//     {
//         std::for_each(shape.begin(), shape.end(), [](const Line& l) {
//             l.Draw(Param::red, Param::line_width * 2);
//         });
//     }

//     void Translate(const Vector& displacement)
//     {
//         std::for_each(shape.begin(), shape.end(), [&](Line& l) { l.Translate(displacement); });
//     }

//     float Min_t(const Pawn& moving_pawn) const
//     {
//         std::vector<float> t;
//         t.reserve(shape.size());

//         for (const Line& line : shape)
//             t.push_back(
//                 collision::Circle_vs_line(
//                     moving_pawn.Shape(),
//                     line,
//                     moving_pawn.Last_translation()
//                 )
//             );

//         return *std::min_element(t.begin(), t.end());
//     }

//     X Mirror_y(const Vector& point) const
//     {
//         X temp = *this;

//         std::transform(shape.begin(), shape.end(), temp.shape.begin(), [&](const Line& l)
//         {
//             return l.Mirror_y(point);
//         });
        
//         return temp;
//     }

//     X Mirror_x(const Vector& point) const
//     {
//         X temp = *this;

//         std::transform(shape.begin(), shape.end(), temp.shape.begin(), [&](const Line& l)
//         {
//             return l.Mirror_x(point);
//         });
        
//         return temp;
//     }
// private:
//     float size;
//     std::array<Line, 2> shape;
// };

// class Window
// {
// public:
//     Window(const Vector& start, const Vector& end)
//     :
//         shape{start, end}
//     {}

//     void Draw() const
//     {
//         shape.Draw(Param::blue, Param::line_width * 2);
//     }

//     const Line& Shape() const
//     {
//         return shape;
//     }

//     void Translate(const Vector& displacement)
//     {
//         shape.Translate(displacement);
//     }

//     Window Mirror_y(const Vector& point) const
//     {
//         Window temp = *this;
//         temp.shape = temp.shape.Mirror_y(point);
//         return temp;
//     }

//     Window Mirror_x(const Vector& point) const
//     {
//         Window temp = *this;
//         temp.shape = temp.shape.Mirror_x(point);
//         return temp;
//     }
// private:
//     Line shape;
// };

void Map::Draw() const
{
    clipper.Draw();
    fence.Draw();
    for (const Wall& w : wall)
        w.Draw();

    // for (const Glass& g : glass)
    //     g.Draw();

    // for (const Tree& t : tree)
    //     t.Draw();

    // for (const X& x : xs)
    //     x.Draw();
}

Vector Map::Magenta_lives_start_position() const
{
    return fence.Top_right() + Vector(1.5, 0.5) * Param::unit_length;
}

Vector Map::Cyan_lives_start_position() const
{
    return fence.Top_left() + Vector(-1.5, 0.5) * Param::unit_length;
}

const Rectangle &Map::Fence_shape() const
{
    return fence.Shape();
}

const Rectangle& Map::Wall_shape(unsigned int index) const
{
    return wall.at(index).Shape();
}

// void Map::Reflect_and_hurt(Player *const player) const
// {
//     float t = Collision::Circle_inside_rectangle(player->Shape(), fence.Shape(), player->Last_translation());

//     if (t == 2)
//         return;

//     player->Retreat(1 - t);
// }

    // void Reflect(Player& moving_pawn) const
    // {
    //     std::for_each(walls.begin(), walls.end(), [&](const Wall& wall) {
    //         float t = collision::Circle_vs_rectangle(
    //             moving_pawn.Shape(),
    //             wall.Shape(),
    //             moving_pawn.Last_translation()
    //         );

    //         if (t == 2)
    //             return;

    //         moving_pawn.Retreat(1 - t);
    //         moving_pawn.Stop();
    //     });
    // }

    // void Tree_stop(Pawn& moving_pawn) const
    // {
    //     std::for_each(trees.begin(), trees.end(), [&](const Tree& tree) {
    //         float t = tree.Min_t(moving_pawn);

    //         if (t == 2)
    //             return;

    //         moving_pawn.Retreat(1 - t);
    //         moving_pawn.Stop();
    //     });
    // }

    // void X_kill(Pawn& moving_pawn, std::set<Pawn *> &dying_pawns) const
    // {
    //     std::for_each(xs.begin(), xs.end(), [&](const X& x) {
    //         float t = x.Min_t(moving_pawn);

    //         if (t == 2 || Pawn::Vanish_immediately())
    //             return;

    //         moving_pawn.Retreat(1 - t);
    //         moving_pawn.Stop();
    //         dying_pawns.insert(&moving_pawn);
    //     });
    // }

    // void Window_only_shoot(Pawn& moving_pawn) const
    // {
    //     std::for_each(windows.begin(), windows.end(), [&](const Window& window) {
    //         float t = collision::Circle_vs_line(
    //             moving_pawn.Shape(),
    //             window.Shape(),
    //             moving_pawn.Last_translation()
    //         );

    //         if (t != 2)
    //             Pawn::Vanish_immediately(true);
    //     });
    // }

Map::Map(const Vector& size)
// Map::Map(const Vector& size, float the_number_of_wall, float the_number_of_glass, float the_number_of_xs, float the_number_of_tree)
:
    fence{
        (Vector(Param::window_width, Param::window_height) - size) / 2,
        size
    },
    clipper{fence.Shape()}
{
    // wall.reserve(the_number_of_wall);
    // glass.reserve(the_number_of_glass);
    // xs.reserve(the_number_of_xs);
    // tree.reserve(the_number_of_tree);
}

Map_1::Map_1()
:
    Map{Vector(720, 720)}
    // Map{Vector(720, 720), 0, 0, 0, 0}
{
    Arrange_wall();
    // Arrange_windows();
    // Arrange_xs();
    // Arrange_trees();
}

Vector Map_1::Magenta_spawn_position() const
{
    return (fence.Top_right() + fence.Bottom_right()) / 2 + Vector(-1.5, 0) * Param::unit_length;
}

Vector Map_1::Cyan_spawn_position() const
{
    return (fence.Top_left() + fence.Bottom_left()) / 2 + Vector(1.5, 0) * Param::unit_length;
}

void Map_1::Arrange_wall()
{
    float temp = fence.Height() / 5;

    wall.emplace_back(
        fence.Origin() + Vector(temp, temp),
        Vector(temp, temp)
    );

    wall.push_back(wall.front().Mirror_y(fence.Center()));
    wall.push_back(wall.front().Mirror_x(fence.Center()));
    wall.push_back(wall.back().Mirror_y(fence.Center()));
}

    // void Arrange_windows()
    // {
    //     windows.emplace_back(
    //         Vector(0, 0),
    //         Vector(0, fence.Height() / 9)
    //     );

    //     windows.emplace_back(
    //         Vector(0, 0),
    //         Vector(fence.Height() / 9, 0)
    //     );

    //     windows.front().Translate(fence.Origin());
    //     windows.front().Translate(Vector(fence.Height() / 3, 0));

    //     windows.back().Translate(fence.Origin());
    //     windows.back().Translate(Vector(0, fence.Height() / 3));

    //     for (int i = 0; i < 2; i++)
    //         windows.emplace_back(
    //             windows.at(i).Mirror_y(fence.Center())
    //         );

    //     for (int i = 0; i < 4; i++)
    //         windows.emplace_back(
    //             windows.at(i).Mirror_x(fence.Center())
    //         );
    // }

    // void Arrange_xs()
    // {
    //     xs.emplace_back(
    //         fence.Origin(),
    //         fence.Height() / 9
    //     );

    //     xs.front().Translate(Vector(1, 1) * fence.Height() / 9 * 2);

    //     xs.emplace_back(
    //         xs.front().Mirror_x(fence.Center())
    //     );

    //     for (int i = 0; i < 2; i++)
    //         xs.emplace_back(
    //             xs.at(i).Mirror_y(fence.Center())
    //         );
    // }

    // void Arrange_trees()
    // {
    //     trees.emplace_back(
    //         Vector(fence.Height(), fence.Height()) / 9 * 2.5,
    //         fence.Height() / 9
    //     );
    // }
