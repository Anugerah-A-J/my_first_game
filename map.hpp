#include "param.hpp"
#include "geometry.hpp"
#include <algorithm>
#include <vector>
#include <array>
#pragma once

class Wall
{
public:
    Wall(const Vector& origin, const Vector& size)
    :
        shape{
            origin,
            size
        }
    {}

    void Draw() const { shape.Draw(param::yellow); }

    const Rectangle& Shape() const { return shape; }

    void Translate(const Vector& displacement) { shape.Translate(displacement); }

    float Width() const { return shape.Width(); }

    float Height() const { return shape.Height(); }

    Wall Mirror_x(const Vector& point) const
    {
        Wall temp = *this;
        temp.shape = temp.shape.Mirror_x(point);
        return temp;
        // return Wall(shape.Mirror_x(point));
    }

    Wall Mirror_y(const Vector& point) const
    {
        Wall temp = *this;
        temp.shape = temp.shape.Mirror_y(point);
        return temp;
        // return Wall(shape.Mirror_y(point));
    }
private:
    Rectangle shape;
    // Wall(const Rectangle& shape): shape{shape} {}
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
        std::array<float, 6> xs {1, 0.5f, -0.5f, -1, -0.5f, 0.5f};
        std::array<float, 6> ys {0, 0.5f, 0.5f, 0, -0.5f, -0.5f};

        std::for_each(shape.begin(), shape.end(), [&, i = 0](Circle& c) mutable
        {
            c.Translate(
                2 * c.Radius() * xs.at(i),
                2 * c.Radius() * ys.at(i) * param::sqrt_3
            );

            i++;
        });
    }

    void Draw() const
    {
        std::for_each(shape.begin(), shape.end(), [](const Circle& c)
        {
            c.Draw(param::green);
        });

        filler.Draw(param::green);
    }

    void Translate(const Vector& displacement)
    {
        std::for_each(shape.begin(), shape.end(), [&](Circle& c)
        {
            c.Translate(displacement);
        });

        filler.Translate(displacement);
    }
    
    void Translate(float x, float y)
    {
        std::for_each(shape.begin(), shape.end(), [&](Circle& c)
        {
            c.Translate(x, y);
        });

        filler.Translate(x, y);
    }

    float Diameter() const { return diameter; }

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
private:
    float diameter;
    std::vector<Circle> shape;
    Circle filler;
};

class X
{
public:
    X(const Vector& center, float size)
    :
        size{size},
        shape{
            Line(center, center + Vector(size, size) / 2),
            Line(center, center - Vector(size, size) / 2),
            Line(center, center + Vector(-size, size) / 2),
            Line(center, center + Vector(size, -size) / 2)
        }
    {}

    void Draw() const
    {
        std::for_each(shape.begin(), shape.end(), [](const Line& l)
        {
            l.Draw(param::red, param::line_width * 2);
        });
    }

    void Translate(const Vector& displacement)
    {
        std::for_each(shape.begin(), shape.end(), [&](Line& l)
        {
            l.Translate(displacement);
        });
    }

    float Size() const { return size; }
private:
    float size;
    std::array<Line, 4> shape;
};

class Window
{
public:
    Window(const Vector& start, const Vector& end): shape{start, end} {}

    void Draw() const { shape.Draw(param::blue, param::line_width * 2); }

    void Translate(const Vector& displacement) { shape.Translate(displacement); }

    float Length() const { return shape.Length(); }
private:
    Line shape;
};

class Map_1
{
public:
    Map_1(const Fence& fence):
        fence{fence},
        walls{6, Wall(fence.Origin(), Vector(param::unit_length, param::unit_length) * 6)},
        windows{4, Window(fence.Origin(), fence.Origin() + Vector(0, walls.front().Height()))},
        xs{5, X(fence.Origin(), param::unit_length * 6)},
        trees{6, Tree(fence.Center(), param::unit_length * 6)}
    {
        arrange_walls();
        arrange_windows();
        arrange_xs();
        arrange_trees();
    }

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
private:
    const Fence& fence;
    std::vector<Wall> walls;
    std::vector<Window> windows;
    std::vector<X> xs;
    std::vector<Tree> trees;

    void arrange_walls()
    {
        std::vector<Wall> corners {3, walls.front()};
        corners.at(1).Translate(Vector(corners.front().Width(), 0));
        corners.at(2).Translate(Vector(0, corners.front().Height()));

        std::for_each(walls.begin(), walls.end(), [&, i = 0](Wall& wall) mutable
        {
            if (i % 2 == 0)
                wall.Translate(Vector(fence.Width() / 4 - wall.Width(), 0));
            else
                wall.Translate(Vector(fence.Width() * 3 / 4, 0));

            wall.Translate(Vector(0, fence.Height() / 2 - wall.Height() / 2));
            i++;
        });

        std::for_each(walls.begin(), walls.begin() + 2, [](Wall& wall)
        {
            wall.Translate(Vector(0, -wall.Height() * 2));
        });

        std::for_each(walls.end() - 2, walls.end(), [](Wall& wall)
        {
            wall.Translate(Vector(0, wall.Height() * 2));
        });

        walls.insert(walls.end(), corners.begin(), corners.end());

        std::transform(corners.begin(), corners.end(), corners.begin(), [&](const Wall& corner)
        {
            return corner.Mirror_x(fence.Center());
        });
        walls.insert(walls.end(), corners.begin(), corners.end());

        std::transform(corners.begin(), corners.end(), corners.begin(), [&](const Wall& wall)
        {
            return wall.Mirror_y(fence.Center());
        });
        walls.insert(walls.end(), corners.begin(), corners.end());

        std::transform(corners.begin(), corners.end(), corners.begin(), [&](const Wall& wall)
        {
            return wall.Mirror_x(fence.Center());
        });
        walls.insert(walls.end(), corners.begin(), corners.end());
    }

    void arrange_windows()
    {
        std::for_each(windows.begin(), windows.end(), [&, i = 0](Window& window) mutable
        {
            if (i % 2 == 0)
                window.Translate(Vector(fence.Width() / 4 - walls.front().Width() / 2, 0));
            else
                window.Translate(Vector(fence.Width() * 3 / 4 + walls.front().Width() / 2, 0));

            window.Translate(Vector(0, fence.Height() / 2 - window.Length() / 2));

            i++;
        });

        std::for_each(windows.begin(), windows.begin() + 2, [](Window& window)
        {
            window.Translate(Vector(0, -window.Length()));
        });

        std::for_each(windows.end() - 2, windows.end(), [](Window& window)
        {
            window.Translate(Vector(0, window.Length()));
        });
    }

    void arrange_xs()
    {
        std::for_each(xs.begin(), xs.end(), [&](X& x)
        {
            x.Translate(Vector(fence.Width() / 2, fence.Height() / 2));
        });

        std::array<int, 4> widths {1, -1, -1, 1};
        std::array<int, 4> heights {-1, -1, 1, 1};

        for (int i = 0; i < 4; i++)
        {
            xs.at(i + 1).Translate(Vector(
                (fence.Width() / 8 - xs.at(i).Size() / 2) * widths.at(i),
                (fence.Width() / 8 - xs.at(i).Size() / 2) * heights.at(i)
            ));
        }
        
    }

    void arrange_trees()
    {
        std::for_each(trees.begin(), trees.end(), [&](Tree& tree)
        {
            tree.Translate(Vector(0, fence.Height() / 2 - tree.Diameter() / 2));
        });

        std::array<float, 5> xs {1, 0.5f, 0, -0.5f, -1};
        std::array<float, 5> ys {0, -0.5f, -1, -0.5f, 0};

        std::for_each(trees.begin() + 1, trees.end(), [&, i = 0](Tree& t) mutable
        {
            t.Translate(
                t.Diameter() * xs.at(i),
                t.Diameter() * ys.at(i) * param::sqrt_3
            );

            i++;
        });

        std::vector<Tree> temp = trees;

        std::transform(temp.begin(), temp.end(), temp.begin(), [&](const Tree& t)
        {
            return t.Mirror_x(fence.Center());
        });

        trees.insert(trees.end(), temp.begin(), temp.end());
    }
};