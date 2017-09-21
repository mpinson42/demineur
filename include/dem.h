#ifndef DEM_H
# define DEM_H

#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <time.h>

#define W 1080
#define H 1080

typedef	struct		s_gen
{
	char **map;
	char **map_min;
	char **map_0;
	char **clic;
	char **drap;
	char **argv;
	int	argc;
	int bmb;
	int perdu;
	void			*win;
	void			*mlx;
	void			*img;
	int				bpp;
	int				s_l;
	int				endian;
	int				red;
	int				blue;
	int				green;
	int 			clic_x;
	int 			clic_y;
	int 			clic_x_f;
	int 			clic_y_f;
	char *img_ptr;
	int x;
	int y;
}					t_gen;

int ft_mouse(int button, int x,int y, t_gen *g);
int		red_cross(t_gen *g);
int		key_pressed(int kc, t_gen *g);
void ft_print_map(t_gen *g, char **map);
void ft_draw_map(t_gen *g);
#endif