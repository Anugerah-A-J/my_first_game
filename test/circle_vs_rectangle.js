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

const line = new Line();

const ctx = canvas.getContext("2d");

canvas.addEventListener("mousemove", function(info){
    circle.center = {x: info.offsetX, y: info.offsetY};

    const half_length = new Vector(circle_radius, circle_radius);
    half_length.multiply(Math.SQRT1_2);

    line.start = subtraction(
        circle.center,
        half_length
    );
    line.end = addition(
        circle.center,
        half_length
    );
    draw();
    // console.log("start : ", line.start);
    // console.log("center: ", circle.center);
    // console.log("end   : ", line.end);
});

// canvas.addEventListener("wheel")

function draw()
{
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.strokeStyle = "white";
    ctx.beginPath();

    circle.draw(ctx);
    rectangle.draw(ctx);
    circle_vs_rectangle.draw(ctx);
    line.draw(ctx);
    
    ctx.stroke();
};