

#include <stdio.h>
#include <mlx.h>

typedef struct s_player
{
    void    *player;
    char    *addr;
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

void    put_pixel(t_player *player, int x, int y, int color)
{
    char *offset;

    offset = player->addr + (y * player->line_lenght + x * (player->bits_per_pixel / 8));
    *(unsigned int*)offset = color;
}

void    create_player(t_player *player)
{
    player->pos_x = 225;
    player->pos_y = 225;
    int x = 0;
    int y = 0;

    player->player = mlx_new_image(player->mlx_ptr, 50, 50);
    player->addr = mlx_get_data_addr(player->player, &player->bits_per_pixel, &player->line_lenght, &player->endian);
    while (x <= 50)
    {
        while (y <= 50)
        {
            put_pixel(player, x, y, 0xff007f);
            y++;
        }
        x++;
        y = 0;
    }
    mlx_put_image_to_window(player->mlx_ptr, player->win_ptr, player->player, player->pos_x, player->pos_y);
}

int     go_down(t_player *player)
{
    
    int x = player->pos_x;
    int y = player->pos_y;
    clear_pixels(player, x, y, 500, 500, 0xffffff);
    player->pos_y += 10;
    mlx_put_image_to_window(player->mlx_ptr, player->win_ptr, player->player, player->pos_x, player->pos_y);

    return 0;
}

int     go_up(t_player *player)
{
    
    int x = player->pos_x;
    int y = player->pos_y;
    clear_pixels(player, x, y, 500, 500, 0xffffff);
    player->pos_y -= 10;
    mlx_put_image_to_window(player->mlx_ptr, player->win_ptr, player->player, player->pos_x, player->pos_y);

    return 0;
}

int     go_left(t_player *player)
{
    
    int x = player->pos_x;
    int y = player->pos_y;
    clear_pixels(player, x, y, 500, 500, 0xffffff);
    player->pos_x -= 10;
    mlx_put_image_to_window(player->mlx_ptr, player->win_ptr, player->player, player->pos_x, player->pos_y);

    return 0;
}

int     go_right(t_player *player)
{
    
    int x = player->pos_x;
    int y = player->pos_y;
    clear_pixels(player, x, y, 500, 500, 0xffffff);
    player->pos_x += 10;
    mlx_put_image_to_window(player->mlx_ptr, player->win_ptr, player->player, player->pos_x, player->pos_y);

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
    clear_pixels(&player, 0, 0, 500, 500, 0xffffff);
    create_player(&player);
    mlx_key_hook(player.win_ptr, key_hook, &player);
    mlx_loop(player.mlx_ptr);
}

