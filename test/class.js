class Vector
{
    constructor(x = 0, y = 0)
    {
        this.x = x;
        this.y = y;
    };

    copy()
    {
        return new Vector(this.x, this.y);
    };

    magsq()
    {
        return this.x * this.x + this.y * this.y;
    };

    add(vector = new Vector())
    {
        this.x += vector.x;
        this.y += vector.y;
    };

    subtract(vector = new Vector())
    {
        this.x -= vector.x;
        this.y -= vector.y;
    };

    multiply(factor = 1)
    {
        this.x *= factor;
        this.y *= factor;
    };
};

function addition(vector_1 = new Vector(), vector_2 = new Vector())
{
    return new Vector(
        vector_1.x + vector_2.x,
        vector_1.y + vector_2.y
    );
}

function subtraction(vector_1 = new Vector(), vector_2 = new Vector())
{
    return new Vector(
        vector_1.x - vector_2.x,
        vector_1.y - vector_2.y
    );
}

function dot(vector_1 = new Vector(), vector_2 = new Vector())
{
    return vector_1.x * vector_2.x + vector_1.y * vector_2.y;
};

class Line
{
    constructor(start = new Vector(), end = new Vector())
    {
        this.start = start;
        this.end = end;
        this.radius = Math.sqrt(subtraction(start, end).magsq());
        this.sin = (end.y - start.y) / this.radius;
        this.cos = (end.x - start.x) / this.radius;
    };

    draw(ctx)
    {
        ctx.moveTo(this.start.x, this.start.y);
        ctx.lineTo(this.end.x, this.end.y)
    };

    translate(displacement = new Vector())
    {
        this.start.add(displacement);
        this.end.add(displacement);
    };

    translate_to(where = this.start)
    {
        this.start = where;

        this.end.x = this.start.x + this.cos * this.radius;
        this.end.y = this.start.y + this.sin * this.radius;
    };

    rotate(degree = 0)
    {
        const radian = degree / 180 * Math.PI;

        const new_sin = this.sin * Math.cos(radian) + this.cos * Math.sin(radian);
        const new_cos = this.cos * Math.cos(radian) - this.sin * Math.sin(radian);
        
        this.sin = new_sin;
        this.cos = new_cos;

        this.end.x = this.start.x + this.cos * this.radius;
        this.end.y = this.start.y + this.sin * this.radius;
    };
};

class Circle
{
    constructor(center = new Vector(), radius = 0)
    {
        this.center = center;
        this.radius = radius;
    };

    copy()
    {
        return new Circle(this.center, this.radius);
    };
    
    draw(ctx) {
        ctx.moveTo(this.center.x + this.radius, this.center.y);
        ctx.arc(this.center.x, this.center.y, this.radius, 0, Math.PI * 2);
    }
};

class Rectangle
{
    constructor(start = new Vector(), size = new Vector())
    {
        this.start = start;
        this.size = size;
    };
    
    draw(ctx)
    {
        ctx.rect(this.start.x, this.start.y, this.size.x, this.size.y);
    };

    top()
    {
        return new Line(
            this.start.copy(),
            addition(this.start, new Vector(this.size.x, 0))
        );
    };

    right()
    {
        const end = addition(this.start, this.size);
        return new Line(
            end.copy(),
            subtraction(end, new Vector(0, this.size.y))
        );
    };

    bottom()
    {
        const end = addition(this.start, this.size);
        return new Line(
            end.copy(),
            subtraction(end, new Vector(this.size.x, 0))
        );
    };

    left()
    {
        return new Line(
            this.start.copy(),
            addition(this.start, new Vector(0, this.size.y))
        );
    };
};

class Circle_vs_Rectangle
{
    constructor(circle = new Circle(), rectangle = new Rectangle())
    {
        this.top = rectangle.top();
        this.right = rectangle.right();
        this.bottom = rectangle.bottom();
        this.left = rectangle.left();

        this.top_left = circle.copy();
        this.top_right = circle.copy();
        this.bottom_right = circle.copy();
        this.bottom_left = circle.copy();

        this.top_left.center = this.top.start.copy();
        this.top_right.center = this.top.end.copy();
        this.bottom_right.center = this.bottom.start.copy();
        this.bottom_left.center = this.bottom.end.copy();

        this.top.translate(new Vector(0, -circle.radius));
        this.right.translate(new Vector(circle.radius, 0));
        this.bottom.translate(new Vector(0, circle.radius));
        this.left.translate(new Vector(-circle.radius, 0));
    };

    draw(ctx)
    {
        this.top.draw(ctx);
        this.right.draw(ctx);
        this.bottom.draw(ctx);
        this.left.draw(ctx);

        this.top_left.draw(ctx);
        this.top_right.draw(ctx);
        this.bottom_right.draw(ctx);
        this.bottom_left.draw(ctx);
    };

    intersect(line = new Line())
    {
        const ts = [];

        ts.push(intersect_line_vs_line(line, this.top));
        ts.push(intersect_line_vs_line(line, this.right));
        ts.push(intersect_line_vs_line(line, this.bottom));
        ts.push(intersect_line_vs_line(line, this.left));

        ts.push(intersect_line_vs_circle(line, this.top_left));
        ts.push(intersect_line_vs_circle(line, this.top_right));
        ts.push(intersect_line_vs_circle(line, this.bottom_right));
        ts.push(intersect_line_vs_circle(line, this.bottom_left));

        return Math.min(...ts);
    };
};

function intersect_line_vs_line(line1 = new Line(), line2 = new Line())
{
    const A = subtraction(line1.end ,line1.start);
    const B = subtraction(line2.end ,line2.start);
    const C = subtraction(line1.start ,line2.start);

    const t_numerator = B.y * C.x - B.x * C.y;
    const u_numerator = C.y * A.x - C.x * A.y;
    const denominator = A.y * B.x - A.x * B.y;

    // std::cout << "    t num: " << t_numerator << "\n";
    // std::cout << "    u num: " << u_numerator << "\n";
    // std::cout << "    denom: " << denominator << "\n";
    // std::cout << "    t: " << t_numerator / denominator << "\n";
    // std::cout << "    u: " << u_numerator / denominator << "\n";

    // // t < 0 and u < 0
    // if (denominator > 0 && (t_numerator < 0 || u_numerator < 0))
    //     return 2;
    // if (denominator < 0 && (t_numerator > 0 || u_numerator > 0))
    //     return 2;

    // // t > 1 and u > 1
    // if (denominator > 0 && (t_numerator > denominator || u_numerator > denominator))
    //     return 2;
    // if (denominator < 0 && (t_numerator < denominator || u_numerator < denominator))
    //     return 2;

    // if (equal(denominator, 0, 0.05f))
    if (denominator == 0)
        return 2;

    const t = t_numerator / denominator;
    const u = u_numerator / denominator;

    if (t < 0 || t > 1 || u < 0 || u > 0)
    // if (t < 0 || t > 1)
        return 2;

    return t;
};

function intersect_line_vs_circle(line, circle)
{
    const X = subtraction(line.start, circle.center);
    const Y = subtraction(line.end, line.start);

    const a = dot(Y, Y);
    const b = 2 * dot(X, Y);
    const c = dot(X, X) - circle.radius * circle.radius;

    let discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return 2;
    }
    else
    {
        discriminant = Math.sqrt(discriminant);

        // Compute min and max solutions of t
        const t_min = (-b - discriminant) / (2 * a);
        const t_max = (-b + discriminant) / (2 * a);
        
        // Check whether either t is within bounds of segment
        if (t_min >= 0 && t_min <= 1)
        {
            return t_min;
        }
        else if (t_max >= 0 && t_max <= 1)
        {
            return t_max;
        }
        else
        {
            return 2;
        }
    }
};