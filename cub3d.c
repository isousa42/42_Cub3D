


#include <stdio.h>
#include <mlx.h>

int main()
{
    void    *mlx_ptr;
    void    *win_ptr;
    int     y;
    int     x;
    int     max_x;
    int     max_y;
    int     pixel;
    int pos_x;
    int pos_y;

    y = 0;
    x = 0;
    max_x = 1000;
    max_y = 1000;
    pos_x = max_x / 2 - 50;
    pos_y = max_y / 2 - 50;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, max_x, max_y, "Cub3D");
    while (x <= max_x)
    {
        while (y <= max_y)
        {
            pixel = mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xffffff);
            y++;
        }
        x++;
        y = 0;
    }
    while (pos_x <= (max_x / 2) + 50)
    {
        while (pos_y <= (max_y / 2) + 50)
        {
            pixel = mlx_pixel_put(mlx_ptr, win_ptr, pos_x, pos_y, 0xff007f);
            pos_y++;
        }
        pos_x++;
        pos_y = max_y / 2 - 50;
    }
    mlx_loop(mlx_ptr);
}

