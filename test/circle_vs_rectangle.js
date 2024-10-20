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

const ctx = canvas.getContext("2d");

canvas.addEventListener("mousemove", function(info){
    circle.center = {x: info.offsetX, y: info.offsetY};
    draw();
});

function draw()
{
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.strokeStyle = "white";
    ctx.beginPath();

    circle.draw(ctx);
    rectangle.draw(ctx);
    circle_vs_rectangle.draw(ctx);
    
    ctx.stroke();
};

function addition(vector_1, vector_2)
{
    return new Vector(
        vector_1.x + vector_2.x,
        vector_1.y + vector_2.y
    );
}

function subtraction(vector_1, vector_2)
{
    return new Vector(
        vector_1.x - vector_2.x,
        vector_1.y - vector_2.y
    );
}