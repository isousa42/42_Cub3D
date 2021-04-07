


#include <stdio.h>
#include <mlx.h>

typedef struct	s_fl
{
	int		pixel_1;
	int		pixel_2;
	int		pixel_3;
	int		pixel_4;
    int		pixel_5;
	int		pixel_6;
	int		pixel_7;
	int		pixel_8;

}				t_flags;

int main()
{
    void    *mlx_ptr;
    void    *win_ptr;
    struct s_fl    pixels;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Cub3D");
    pixels.pixel_1 = mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xff007f);
    pixels.pixel_2 = mlx_pixel_put(mlx_ptr, win_ptr, 251, 250, 0xff007f);
    pixels.pixel_3 = mlx_pixel_put(mlx_ptr, win_ptr, 250, 251, 0xff007f);
    pixels.pixel_4 = mlx_pixel_put(mlx_ptr, win_ptr, 251, 251, 0xff007f);
    pixels.pixel_5 = mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xff007f);
    pixels.pixel_6 = mlx_pixel_put(mlx_ptr, win_ptr, 251, 250, 0xff007f);
    pixels.pixel_7 = mlx_pixel_put(mlx_ptr, win_ptr, 250, 251, 0xff007f);
    pixels.pixel_8 = mlx_pixel_put(mlx_ptr, win_ptr, 251, 251, 0xff007f);
    mlx_loop(mlx_ptr);
    
}