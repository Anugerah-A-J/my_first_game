```
Vector A = line1.get_end() - line1.get_start();
Vector B = line2.get_end() - line2.get_start();
Vector C = line1.get_start() - line2.get_start();

float numerator = B.get_y() * C.get_x() - B.get_x() * C.get_y();
float denominator = A.get_y() * B.get_x() - A.get_x() * B.get_y();
```
$$
L_1 = \begin{bmatrix} x_1 \\ y_1 \end{bmatrix} + t \begin{bmatrix} x_2 - x_1 \\ y_2 - y_1 \end{bmatrix}
$$
$$
L_2 = \begin{bmatrix} x_3 \\ y_3 \end{bmatrix} + u \begin{bmatrix} x_4 - x_3 \\ y_4 - y_3 \end{bmatrix}
$$
$$
A = \begin{bmatrix} x_2 - x_1 \\ y_2 - y_1 \end{bmatrix}
$$
$$
B = \begin{bmatrix} x_4 - x_3 \\ y_4 - y_3 \end{bmatrix}
$$
$$
C = \begin{bmatrix} x_1 - x_3 \\ y_1 - y_3 \end{bmatrix}
$$
$$
t = \frac{(y_4 - y_3)(x_1 - x_3) - (x_4 - x_3)(y_1 - y_3)}
{(y_2 - y_1)(x_4 - x_3) - (x_2 - x_1)(y_4 - y_3)}
$$
$$
t = \frac{(x_1 - x_3)(y_4 - y_3) - (y_1 - y_3)(x_4 - x_3)}
{-(x_2 - x_1)(y_4 - y_3) + (y_2 - y_1)(x_4 - x_3)}
$$
$$
t = \frac{-(x_1 - x_3)(y_3 - y_4) + (y_1 - y_3)(x_3 - x_4)}
{-(x_1 - x_2)(y_3 - y_4) + (y_1 - y_2)(x_3 - x_4)}
$$
$$
t = \frac{(x_1 - x_3)(y_3 - y_4) - (y_1 - y_3)(x_3 - x_4)}
{(x_1 - x_2)(y_3 - y_4) - (y_1 - y_2)(x_3 - x_4)}
$$