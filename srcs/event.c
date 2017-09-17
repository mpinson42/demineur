#include "dem.h"

int		red_cross(t_gen *g)
{
	(void)g;
	exit(0);
	return (0);
}

void ft_chr_clic(int x, int y, t_gen *g)
{
	int espace = H / g->x;
	int count;
	int test;

	count = 0;
	test = 0;
	while(test < H)
	{
		if(x > test && x <= test + espace)
			g->clic_x = count;
		if(y > test && y <= test + espace)
			g->clic_y = count;
		test += espace;
		count++;
	}
	printf("x = %d y = %d\n", g->clic_x, g->clic_y);
}

void ft_drap() // dessin un drapequ a la case
{

}

void ft_rand(t_gen *g)
{
	int bmb = 10;
	int x;
	int y;
	int i;

	i = 0;
	srand(time(NULL));
	while(i < bmb)
	{
		x = rand()% g->x +0;
		y = rand()% g->x +0;
		if(g->map_min[x][y] == 'X' || (g->clic_x == x && g->clic_y == y))
			continue ;
		g->map_min[x][y] = 'X';
		i++;
	}
	ft_print_map(g, g->map_min);
}

void ft_revel(t_gen *g)
{
	static int  first = 0;

	if(first == 0)
		ft_rand(g);
	if(g->map_min[g->clic_x][g->clic_y] == 'X')
	{
		ft_putstr("game_over\n");
		exit(0);
	}
	g->map[g->clic_x][g->clic_y] = '0';

	first = 1;
}

int ft_mouse(int button, int x,int y, t_gen *g)
{
	ft_chr_clic(x, y, g);
	printf("%d\n", button);
	if(button == 1)
		ft_revel(g);
	if(button == 2)
		ft_drap();
	ft_draw_map(g);
	return(0);
}

int		key_pressed(int kc, t_gen *g)
{
	if(kc == 53)
		exit(0);
	return(0);
}