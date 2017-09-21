#include "dem.h"

void	ft_putpixel_in_img(int x, int y, t_gen *g, unsigned int color)
{
	if ((unsigned long long int)((x * 4) + (y * W * 4)) >
			(unsigned long long int)(W * H * 4) ||
			(unsigned long long int)((x * 4) + (y * W * 4))
			<= 0 || x > W || x < 0 || y < 0 || y > H)
		return ;
	if (color == 0)
	{
		g->img_ptr[(x * 4) + (y * W * 4)] = 0;
		g->img_ptr[(x * 4) + (y * W * 4) + 1] = 0;
		g->img_ptr[(x * 4) + (y * W * 4) + 2] = 0;
		g->img_ptr[(x * 4) + (y * W * 4) + 3] = 0;
	}
	else
	{
		g->img_ptr[(x * 4) + (y * W * 4)] = g->blue;
		g->img_ptr[(x * 4) + (y * W * 4) + 1] = g->green;
		g->img_ptr[(x * 4) + (y * W * 4) + 2] = g->red;
		g->img_ptr[(x * 4) + (y * W * 4) + 3] = 0;
	}
}

int ft_init(t_gen *g, int argc, char **argv)
{
	int x;
	int y;

	g->x = 10; //nb case
	if(argc >= 2)
		g->x = ft_atoi(argv[1]);
	if(g->x < 10 || g->x > 45)
		g->x = 10;

	if(argc >= 3 && (ft_atoi(argv[2]) < 10 || ft_atoi(argv[2]) > g->x * g->x - 9))
		g->bmb = 10;
	else if(argc >= 3)
		g->bmb = ft_atoi(argv[2]);
	
	g->map = (char **)malloc(sizeof(char *) * (g->x + 1));
	g->map_min = (char **)malloc(sizeof(char *) * (g->x + 1));
	g->map_0 = (char **)malloc(sizeof(char *) * (g->x + 1));
	g->clic = (char **)malloc(sizeof(char *) * (g->x + 1));
	g->drap = (char **)malloc(sizeof(char *) * (g->x + 1));
	
	if(g->x < 10)
		return(-1);
	x = 0;
	while(x < g->x)
	{
		y = 0;
		g->map_min[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		g->map[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		g->map_0[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		g->clic[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		g->drap[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		while(y < g->x)
		{
			g->map_min[x][y] = '.';
			g->map[x][y] = '*';
			g->map_0[x][y] = '1';
			g->clic[x][y] = '0';
			g->drap[x][y] = '.';
			y++;
		}
		g->map_min[x][y] = 0;
		g->map[x][y] = 0;
		x++;
	}
	g->map_min[x] = NULL;
	g->map[x] = NULL;
	return(0);
}

void ft_print_map(t_gen *g, char **map)
{
	int x;
	int y;

	x = 0;
	while(x < g->x)
	{
		ft_putendl(map[x]);
		x++;
	}
}

void ft_draw_grille(int x, int y, t_gen *g)
{
	int i = 0;

	g->red = 255 / 2;
	g->blue = 255 / 2;
	g->green = 255 / 2;

	while(i < H)
	{
		ft_putpixel_in_img(x, i, g, 42);
		i++;
	}
	i = 0;
	while(i < H)
	{
		ft_putpixel_in_img(i, y, g, 42);
		i++;
	}

}

void ft_draw_map(t_gen *g)
{
	int x;
	int y;
	int lang = H / g->x;
	int save_x;
	int save_y;
	int bmb;

	x = 0;
	while(x < g->x)
	{
		y = 0;
		while(y < g->x)
		{
			if(g->map_min[x][y] == 'X' && g->perdu == 1)
			{
				g->red = 255;
				g->blue = 0;
				g->green = 0;
			}
			else if(g->map[x][y] == '*')
			{
				g->red = 0;
				g->blue = 255;
				g->green = 0;
			}
			else if(g->map[x][y] == '0' || g->map[x][y] == '-')
			{
				g->red = 255;
				g->blue = 255;
				g->green = 255;
			}
			else
			{
				g->red = 0;
				g->blue = 0;
				g->green = 0;
			}

			save_x = x * lang;
			save_y = y * lang;

			
			while(save_x < (x + 1) * lang)
			{
				save_y = y * lang;
				while(save_y < (y + 1) * lang)
				{
					
					ft_putpixel_in_img(save_x, save_y, g, 42);
					save_y++;
				}
				save_x++;
			}
			ft_draw_grille(x * lang, y * lang, g);





			y++;
		}
		x++;
	}
	ft_draw_grille(x * lang - 1, y * lang - 1, g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	x = 0;
	while(x < g->x)
	{
		y = 0;
		while(y < g->x)
		{
			save_x = x * lang;
			save_y = y * lang;
			if(g->map[x][y] == '*' && g->drap[x][y] == '!')
				mlx_string_put(g->mlx, g->win, save_x + lang / 2, save_y + lang /2, 0x00FF0000, "!");
			if(ft_isalnum(g->map[x][y]))
			{
				char c[2];
				c[0] = g->map[x][y];
				c[1] = 0;
				if(g->map[x][y] == '0')
					mlx_string_put(g->mlx, g->win, save_x + lang / 2, save_y + lang /2, 0x00000000, c);
				else
					mlx_string_put(g->mlx, g->win, save_x + lang / 2, save_y + lang /2, 0x00FFFFFF, c);
			}
			y++;
		}
		x++;
	}
}

int main(int argc, char **argv)
{
	t_gen g;

	ft_bzero(&g, sizeof(g));
	ft_init(&g, argc, argv);
	ft_print_map(&g, g.map);
	g.argv = argv;
	g.argc = argc;

	if (!(g.mlx = mlx_init()))
		return (-1);
	if (!(g.img = mlx_new_image(g.mlx, W, H)))
		return (-1);
	if (!(g.img_ptr = mlx_get_data_addr(g.img, &(g.bpp),
					&(g.s_l), &(g.endian))))
		return (-1);
	if (!(g.win = mlx_new_window(g.mlx, W, H, "demineur")))
		return (-1);
	//g.map[54][54] = '6';
	ft_draw_map(&g);
	mlx_mouse_hook(g.win, &ft_mouse, &g);
	mlx_hook(g.win, 17, (1L << 17), &red_cross, &g);
	mlx_hook(g.win, 2, 1L << 0, &key_pressed, &g);
	mlx_loop(g.mlx);
}