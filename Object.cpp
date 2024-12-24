#include "Object.hpp"
#include "Character.hpp"
#pragma once

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

Clipper::Clipper(const Fence& fence)
: 
    left{
        Vector(0, 0),
        Vector((Param::window_width - fence.Width()) / 2, Param::window_height)
    },
    top{
        Vector(0, 0),
        Vector(Param::window_width, (Param::window_height - fence.Height()) / 2)
    },
    right{
        fence.Top_right(),
        Vector(Param::window_width, Param::window_height)
    },
    bottom{
        fence.Bottom_left(),
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

Fence::Fence()
:
    shape{
        Vector(2 * Param::unit_length, Param::unit_length),
        Vector(Param::window_width - 4 * Param::unit_length, Param::window_height - 2 * Param::unit_length)
    },
    color{Param::red},
    line_width{Param::line_width * 2}
{}

void Fence::Draw() const
{
    shape.Draw(color, line_width);
}

const Vector& Fence::Origin() const
{
    return shape.Origin();
}

const Vector& Fence::Top_right() const
{
    return shape.Top_right();
}

const Vector& Fence::Bottom_left() const
{
    return shape.Bottom_left();
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

void Fence::Hurt(Player& player) const
{
    float t = Collision::Circle_inside_rectangle(player.Shape(), shape, player.Last_translation());

    if (t == 2 || Pawn::Vanish_immediately())
        return;

    moving_pawn.Retreat(1 - t);
    moving_pawn.Stop();
    dying_pawns.insert(&moving_pawn);
}

class Wall
{
public:
    Wall(const Vector& origin, const Vector& size)
    :
        shape{origin, size}
    {}

    void Draw() const
    {
        shape.Draw(Param::yellow);
    }

    const Rectangle& Shape() const
    {
        return shape;
    }

    void Center(const Vector& point)
    {
        shape.Center(point);
    }
private:
    Rectangle shape;
};

class Tree
{
public:
    Tree(const Vector& center, float overall_diameter)
    :
        diameter{overall_diameter},
        shape{6, Circle(center, overall_diameter / 6)},
        filler{center, shape.front().Radius() * 1.7321f}
    {
        std::array<float, 6> xs{1, 0.5f, -0.5f, -1, -0.5f, 0.5f};
        std::array<float, 6> ys{0, 0.5f, 0.5f, 0, -0.5f, -0.5f};

        std::for_each(shape.begin(), shape.end(), [&, i = 0](Circle& c) mutable {
            c.Translate(
                2 * c.Radius() * Vector(xs.at(i), ys.at(i) * Param::sqrt_3)
            );

            i++;
        });
    }

    void Draw() const
    {
        std::for_each(shape.begin(), shape.end(), [](const Circle& c) { c.Draw(Param::green); });

        filler.Draw(Param::green);
    }

    void Translate(const Vector& displacement)
    {
        std::for_each(shape.begin(), shape.end(), [&](Circle& c) { c.Translate(displacement); });

        filler.Translate(displacement);
    }

    Tree Mirror_x(const Vector& point) const
    {
        Tree temp = *this;

        temp.filler = temp.filler.Mirror_x(point);

        std::transform(temp.shape.begin(), temp.shape.end(), temp.shape.begin(), [&](const Circle& c) 
        {
            return c.Mirror_x(point);
        });

        return temp;
    }

    Tree Mirror_y(const Vector& point) const
    {
        Tree temp = *this;

        temp.filler = temp.filler.Mirror_y(point);

        std::transform(temp.shape.begin(), temp.shape.end(), temp.shape.begin(), [&](const Circle& c) 
        {
            return c.Mirror_y(point);
        });

        return temp;
    }

    float Min_t(const Pawn& moving_pawn) const
    {
        std::vector<float> t;
        t.reserve(shape.size());

        for (const Circle& circle : shape)
            t.push_back(collision::Circle_vs_circle(moving_pawn.Shape(),
                                                    circle,
                                                    moving_pawn.Last_translation()));

        return *std::min_element(t.begin(), t.end());
    }

private:
    float diameter;
    std::vector<Circle> shape;
    Circle filler;
};

class X
{
public:
    X(const Vector& origin, float size)
    :
        size{size},
        shape{
            Line(origin, origin + Vector(size, size)),
            Line(origin, origin + Vector(size, size)).Mirror_x(origin + Vector(size, size) / 2)
        }
    {}

    void Draw() const
    {
        std::for_each(shape.begin(), shape.end(), [](const Line& l) {
            l.Draw(Param::red, Param::line_width * 2);
        });
    }

    void Translate(const Vector& displacement)
    {
        std::for_each(shape.begin(), shape.end(), [&](Line& l) { l.Translate(displacement); });
    }

    float Min_t(const Pawn& moving_pawn) const
    {
        std::vector<float> t;
        t.reserve(shape.size());

        for (const Line& line : shape)
            t.push_back(
                collision::Circle_vs_line(
                    moving_pawn.Shape(),
                    line,
                    moving_pawn.Last_translation()
                )
            );

        return *std::min_element(t.begin(), t.end());
    }

    X Mirror_y(const Vector& point) const
    {
        X temp = *this;

        std::transform(shape.begin(), shape.end(), temp.shape.begin(), [&](const Line& l)
        {
            return l.Mirror_y(point);
        });
        
        return temp;
    }

    X Mirror_x(const Vector& point) const
    {
        X temp = *this;

        std::transform(shape.begin(), shape.end(), temp.shape.begin(), [&](const Line& l)
        {
            return l.Mirror_x(point);
        });
        
        return temp;
    }
private:
    float size;
    std::array<Line, 2> shape;
};

class Window
{
public:
    Window(const Vector& start, const Vector& end)
    :
        shape{start, end}
    {}

    void Draw() const
    {
        shape.Draw(Param::blue, Param::line_width * 2);
    }

    const Line& Shape() const
    {
        return shape;
    }

    void Translate(const Vector& displacement)
    {
        shape.Translate(displacement);
    }

    Window Mirror_y(const Vector& point) const
    {
        Window temp = *this;
        temp.shape = temp.shape.Mirror_y(point);
        return temp;
    }

    Window Mirror_x(const Vector& point) const
    {
        Window temp = *this;
        temp.shape = temp.shape.Mirror_x(point);
        return temp;
    }
private:
    Line shape;
};

class Map
{
public:
    void Draw() const
    {
        for (const Window& window : windows)
            window.Draw();

        for (const Wall& wall : walls)
            wall.Draw();

        for (const Tree& tree : trees)
            tree.Draw();

        for (const X& x : xs)
            x.Draw();
    }

    void Wall_stop(Pawn& moving_pawn) const
    {
        std::for_each(walls.begin(), walls.end(), [&](const Wall& wall) {
            float t = collision::Circle_vs_rectangle(
                moving_pawn.Shape(),
                wall.Shape(),
                moving_pawn.Last_translation()
            );

            if (t == 2)
                return;

            moving_pawn.Retreat(1 - t);
            moving_pawn.Stop();
        });
    }

    void Tree_stop(Pawn& moving_pawn) const
    {
        std::for_each(trees.begin(), trees.end(), [&](const Tree& tree) {
            float t = tree.Min_t(moving_pawn);

            if (t == 2)
                return;

            moving_pawn.Retreat(1 - t);
            moving_pawn.Stop();
        });
    }

    void X_kill(Pawn& moving_pawn, std::set<Pawn *> &dying_pawns) const
    {
        std::for_each(xs.begin(), xs.end(), [&](const X& x) {
            float t = x.Min_t(moving_pawn);

            if (t == 2 || Pawn::Vanish_immediately())
                return;

            moving_pawn.Retreat(1 - t);
            moving_pawn.Stop();
            dying_pawns.insert(&moving_pawn);
        });
    }

    void Window_only_shoot(Pawn& moving_pawn) const
    {
        std::for_each(windows.begin(), windows.end(), [&](const Window& window) {
            float t = collision::Circle_vs_line(
                moving_pawn.Shape(),
                window.Shape(),
                moving_pawn.Last_translation()
            );

            if (t != 2)
                Pawn::Vanish_immediately(true);
        });
    }

protected:
    Map(
        const Fence& fence,
        float the_number_of_walls,
        float the_number_of_windows,
        float the_number_of_xs,
        float the_number_of_trees
    ):
        fence{fence}
    {
        walls.reserve(the_number_of_walls);
        windows.reserve(the_number_of_windows);
        xs.reserve(the_number_of_xs);
        trees.reserve(the_number_of_trees);
    }

    const Fence& fence;
    std::vector<Wall> walls;
    std::vector<Window> windows;
    std::vector<X> xs;
    std::vector<Tree> trees;
};

class Map_1 : public Map
{
public:
    Map_1(const Fence& fence)
        : Map{fence, 1, 8, 4, 4}
    {
        Arrange_walls();
        Arrange_windows();
        Arrange_xs();
        Arrange_trees();
    }
private:
    void Arrange_walls()
    {
        walls.emplace_back(
            fence.Origin(),
            Vector(fence.Height() / 3, fence.Height() / 3)
        );

        walls.front().Center(fence.Center());
    }

    void Arrange_windows()
    {
        windows.emplace_back(
            Vector(0, 0),
            Vector(0, fence.Height() / 9)
        );

        windows.emplace_back(
            Vector(0, 0),
            Vector(fence.Height() / 9, 0)
        );

        windows.front().Translate(fence.Origin());
        windows.front().Translate(Vector(fence.Height() / 3, 0));

        windows.back().Translate(fence.Origin());
        windows.back().Translate(Vector(0, fence.Height() / 3));

        for (int i = 0; i < 2; i++)
            windows.emplace_back(
                windows.at(i).Mirror_y(fence.Center())
            );

        for (int i = 0; i < 4; i++)
            windows.emplace_back(
                windows.at(i).Mirror_x(fence.Center())
            );
    }

    void Arrange_xs()
    {
        xs.emplace_back(
            fence.Origin(),
            fence.Height() / 9
        );

        xs.front().Translate(Vector(1, 1) * fence.Height() / 9 * 2);

        xs.emplace_back(
            xs.front().Mirror_x(fence.Center())
        );

        for (int i = 0; i < 2; i++)
            xs.emplace_back(
                xs.at(i).Mirror_y(fence.Center())
            );
    }

    void Arrange_trees()
    {
        trees.emplace_back(
            Vector(fence.Height(), fence.Height()) / 9 * 2.5,
            fence.Height() / 9
        );
    }
};