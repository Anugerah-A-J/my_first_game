const circle_radius = canvas.width / 25;
const rect_size_ratio = 0.25;

const circle = new Circle(undefined, circle_radius);

const rectangle = new Rectangle(
    new Vector(
        canvas.width / 2 * (1 - rect_size_ratio),
        canvas.height / 2 * (1 - rect_size_ratio)
    ),
    new Vector(
        canvas.width * rect_size_ratio,
        canvas.height * rect_size_ratio
    )
);

const circle_vs_rectangle = new Circle_vs_Rectangle(circle, rectangle);

const line = new Line(
    circle.center, addition(circle.center.copy(), new Vector(2 * circle.radius, 0))
);

const ctx = canvas.getContext("2d");

canvas.addEventListener("mousemove", (event) => {
    circle.center = {x: event.offsetX, y: event.offsetY};
    line.translate_to(circle.center);
    draw();
});

canvas.addEventListener("wheel", (event) => {
    line.rotate(event.deltaY * 0.1);
    draw();
});

function draw()
{
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // ctx.strokeStyle = "white";
    ctx.beginPath();

    // circle.draw(ctx);
    // rectangle.draw(ctx);
    circle_vs_rectangle.draw(ctx);
    line.draw(ctx);
    check();
    ctx.stroke();
};

function check()
{
    if (circle_vs_rectangle.intersect(line) === 2)
        ctx.strokeStyle = "white";
    else
        ctx.strokeStyle = "red";
};