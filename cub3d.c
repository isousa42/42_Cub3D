

#include <stdio.h>
#include <mlx.h>

typedef struct s_player
{
    void    *player;
    int    *addr;
    int     bits_per_pixel;
    int     line_lenght;
    int     endian;
    int     pos_x;
    int     pos_y;
    void    *win_ptr;
    void    *mlx_ptr;

}               t_player;

void    clear_pixels(t_player *player, int x, int y, int lim_x, int lim_y, int color)
{
    while (x <= lim_x)
    {
        while (y <= lim_y)
        {
            mlx_pixel_put(player->mlx_ptr, player->win_ptr, x, y, color);
            y++;
        }
        x++;
        y = player->pos_y;
    }
}

void	draw_rectangle(t_player *player, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{  
			mlx_pixel_put(player->mlx_ptr, player->win_ptr, player->pos_x + i, player->pos_y + j, 0xffffff);
			j++;
		}
		i++;
	}
}

// void    put_pixel(t_player *player, int x, int y, int color)
// {
//     char *offset;

//     offset = player->addr + (y * player->line_lenght + x * (player->bits_per_pixel / 8));
//     *(unsigned int*)offset = color;
// }

// void    create_player(t_player *player)
// {
//     int x = 0;
//     int y = 0;

//     while (x < 8)
//     {
//         y = 0;
//         while (y < 8)
//         {
//             put_pixel(player, player->pos_x+ x, player->pos_y + y, 0xff007f);
//             y++;
//         }
//         x++;
//     }

int     go_down(t_player *player)
{
    
    player->pos_y += 10;
    return 0;
}

int     go_up(t_player *player)
{
    
    player->pos_y -= 10;
    return 0;
}

int     go_left(t_player *player)
{
    
    player->pos_x -= 10;

    return 0;
}
int     main_loop(t_player *player)
{
    draw_rectangle(player, player->pos_x, player->pos_y);
    // clear_pixels(player, 0, 0, 500, 500, 0xffffff);
    // mlx_put_image_to_window(player->mlx_ptr, player->win_ptr, player->player, 0, 0);
    
    return 0;
}

int     go_right(t_player *player)
{
    
    player->pos_x += 10;

    return 0;
}

int     key_hook(int keycode, t_player *player)
{
    if (keycode == 1)
        go_down(player);
    if (keycode == 13)
        go_up(player);
    if (keycode == 0)
        go_left(player);
    if (keycode == 2)
        go_right(player);
    return 0;
}

int main()
{
    t_player player;

    player.mlx_ptr = mlx_init();
    player.win_ptr = mlx_new_window(player.mlx_ptr, 500, 500, "Cub3D");
    // clear_pixels(&player, 0, 0, 500, 500, 0xffffff);
    // player.player = mlx_new_image(player.mlx_ptr, 500, 500);
    // player.addr = (int *)mlx_get_data_addr(player.player, &player.bits_per_pixel, &player.line_lenght, &player.endian);
    // mlx_put_image_to_window(player.mlx_ptr, player.win_ptr, player.player, 0, 0); 
    player.pos_x = 100;
    player.pos_y = 150;
    mlx_loop_hook(player.mlx_ptr, &main_loop, &player);
    mlx_hook(player.win_ptr, 2, 0, &key_hook, &player);
    

    mlx_loop(player.mlx_ptr);
}

