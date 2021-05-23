#include "mlx.h"
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// #define mapWidth 8
// #define mapHeight 8
#define textWidth 128
#define textHeight 128

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17

#define KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2
#define KEY_ESC 53
#define KEY_RIGHT 124
#define KEY_LEFT 123

typedef struct s_list
{
    void *content;
    struct s_list *next;

}       t_list;

typedef struct s_rc
{
	int j;
	int y;
	float rayDirX0;
	float rayDirY0;
	float rayDirY1;
	float rayDirX1;
	int p;
	float posZ;
	float rowDistance;
	float floorStepX;
	float floorStepY;
	float floorX;
	float floorY;
	int k;
	int cellX;
	int cellY;
	int tx;
	int ty;
	int floorText;
	int ceilingText;
	int colorFC;
	int color;
	int x;
	double cameraX;
	double rayDirX; 
	double rayDirY; 
	int mapX; 
	int mapY; 
	double sideDistX;
	double sideDistY;
	double deltaDistX; 
	double deltaDistY; 
	double perpWallDist;
	int stepX;
	int stepY;
	int hit; 
	int side; 
	int lineHeight;
	int drawStart;
	int drawEnd;
	int textNum;
	double wallX;
	int textX;
	double step;
	double textPos;
	int i;
	int textY;
	double distWall;
	double distPlayer;
	double currentDist;
	double weight;
	double currentFloorX;
	double currentFloorY;
	int floorTextX;
	int floorTextY;
	int checkerBoardPattern;
	int floorTexture;
	double floorXWall;
	double floorYWall;
}		t_rc;

typedef struct s_keys
{
	int key_w;
	int key_s;
	int key_a;
	int key_d;
	int key_esc;
	int key_right;
	int key_left;
}		t_keys;

typedef struct s_image
{
	void	*img;
	int	*data;
	int	size;
	int	bpp;
	int	endian;
	int	img_width;
	int	img_height;
}		t_image;

typedef struct s_sprites
{
	double *sprites_buff;
	double inversion;
	double depthX;
	double depthY;
	double screenX;
	int spriteHeight;
	int drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;
	int sprite;
	int textX;
	int avoid_overflow;
	int sprite_color;
	int textY;
	int move;

}		t_sprites;

typedef struct s_info
{
	void *mlx;
	void *win;
	t_image img;
	t_keys keys;
	t_rc rc;
	t_sprites sprites;
	char **map;
	int	**buff;
	int	**texture;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
	//ceiling rgb
	int rgb_ceiling;
	//floor rgb
	int rgb_floor;

	int size_list;
	int size;
	int start;

	char direction;

	char *file_path;
	

	int     flagF[3];
    int     flagC[3];
	char    *flagNO;
    char    *flagSO;
    char    *flagWE;
    char    *flagEA;
    char    *flagS;

	int r;
	int g;
	int b;

	int r2;
	int g2;
	int b2;

	int take_pic;

	int flagRX;
	int flagRY;

	char **save;
	
	int width;
	int height;
}		t_info;

// cub3d.c
void	rc_loop(t_info *info);
int		first_loop(t_info *info);


// init_test.c
void	load_text(t_info *info);
int	load_img(t_info *info, int *texture, char *path, t_image *img);
void	*ft_memcpy(void *dest, const void *src, size_t n);

// init_info.c
void    ft_init_info(t_info *info);
void	init_play_pos(t_info *info);

// keys.c
int		key_release(int keycode, t_info *info);
int		key_press(int keycode, t_info *info);
int		key_hook(t_info *info);
void	init_key(t_info *info);

// floor.c
void    floor_draw(t_info *info);
void	floor_init(t_info *info);
void	floor_calculations(t_info *info);

int		create_rgb(int r, int g, int b);

// wall.c

void    wall_init(t_info *info);
void    ray_walking(t_info *info);
void    dda_algorithm(t_info *info);
void	wall_calc(t_info *info);
void	wall_text(t_info *info);

// sprites.c
void	sprites_draw(t_info *info, double spriteX, double spriteY, int texture);


//utils.c
void	draw_img(t_info *info);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *str, size_t n);


void	read_file(t_info *info);
int		ft_strlen(char *str);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *src);
int		ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
int	ft_iswall(char c);
int			get_next_line(int fd, char **line);
int     check_resolution(char *line);
void    parse_r(t_info *info, char *line);
void    parse_f(t_info *info, char *line);
void    parse_c(t_info *info, char *line);
int     check_c_f(char *line);
void    parse_variable(t_info *info, char *line, int control);
void    parse_flags(t_info *info,char *save, int control);

int	ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);


void    check_errors_map(char **save, int size);
int     start_map(char **save);
int     counter_map(char **save, int first, int size);
int     check_outside(char **save, int size);
int     check_inside(char **save, int size);
int     check_letters(char **save, int size);
int     check_close(char **save, int size);


int		check_arg(char *arg);

void    take_screenshot(t_info *info);
void	write_image(int file, t_info *info);
int	write_header(int fd, int filesize, t_info *info);
void	conv_int(unsigned char *start, int value);
int	close_window(t_info *info);
void    check_args(int argc, char **argv, t_info *info);
void    init_pos(t_info *info);
void    init_map(t_info *info, t_list *lista);
void    check_width(t_info *info);
void    parse_file(t_info *info, t_list **lista, char *line);
void	init_south_north(t_info *info);
void	init_west_east(t_info *info);
void	text_calc(t_info *info);
void	sprites_calc(t_info *info);
int     check_other_things(char **save, int x, int y);
void     help_check_res(char *line, int *i, int *set_of_n);
void    help_check_cf(char *line, int *i, int *set_of_n);
void	free_text(t_info *info, int control);
int		handle_buff(t_info *info);
void	handle_keys(t_info *info, int keys);
void	init_rgb(t_info *info);
void	sprites_init(t_info *info, double spriteX, double spriteY, int texture);