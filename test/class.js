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



class Line
{
    constructor(start = new Vector(), end = new Vector())
    {
        this.start = start;
        this.end = end;
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
};

class Circle
{
    constructor(center = new Vector(), radius = 0)
    {
        this.center = center;
        this.radius = radius;
    };
    
    draw(ctx) {
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
        this.rectangle = rectangle;
        this.circle = circle;
    };

    draw(ctx)
    {
        const top = this.rectangle.top();
        const right = this.rectangle.right();
        const bottom = this.rectangle.bottom();
        const left = this.rectangle.left();

        ctx.arc(top.start.x, top.start.y, this.circle.radius, 0, Math.PI * 2);
        ctx.arc(top.end.x, top.end.y, this.circle.radius, 0, Math.PI * 2);
        ctx.arc(bottom.start.x, bottom.start.y, this.circle.radius, 0, Math.PI * 2);
        ctx.arc(bottom.end.x, bottom.end.y, this.circle.radius, 0, Math.PI * 2);

        top.translate(new Vector(0, -this.circle.radius));
        right.translate(new Vector(this.circle.radius, 0));
        bottom.translate(new Vector(0, this.circle.radius));
        left.translate(new Vector(-this.circle.radius, 0));

        top.draw(ctx);
        right.draw(ctx);
        bottom.draw(ctx);
        left.draw(ctx);
    };
};