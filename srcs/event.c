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

void ft_drap(t_gen *g) // dessin un drapequ a la case
{
	if(g->drap[g->clic_x][g->clic_y] == '!')
		g->drap[g->clic_x][g->clic_y] = '.';
	else if(g->drap[g->clic_x][g->clic_y] == '.')
		g->drap[g->clic_x][g->clic_y] = '!';
	ft_print_map(g, g->drap);
}

void ft_rand(t_gen *g)
{
	int bmb = 10; //nb bombe
	int x;
	int y;
	int i;

	i = 0;

	if(g->argc >= 3)
	{
		bmb = ft_atoi(g->argv[2]);
	}
	if(bmb < 10 || bmb > g->x * g->x - 9)
		bmb = 10;

	g->bmb = bmb;
	srand(time(NULL));
	g->map[g->clic_x][g->clic_y] = 'L'; // mettre 'L' en haut et en bas et en diagonal pour le 1er clic
	if(g->clic_x > 0)
		g->map[g->clic_x - 1][g->clic_y] = 'L';
	if(g->clic_x < g->x - 1)
		g->map[g->clic_x + 1][g->clic_y] = 'L';
	if(g->clic_y > 0)
		g->map[g->clic_x][g->clic_y - 1] = 'L';
	if(g->clic_y < g->x - 1)
		g->map[g->clic_x][g->clic_y + 1] = 'L';

	if(g->clic_x > 0 && g->clic_y > 0)
		g->map[g->clic_x - 1][g->clic_y - 1] = 'L';
	if(g->clic_x < g->x - 1 &&  g->clic_y < g->x - 1)
		g->map[g->clic_x + 1][g->clic_y + 1] = 'L';
	if(g->clic_y > 0 && g->clic_x < g->x - 1)
		g->map[g->clic_x + 1][g->clic_y - 1] = 'L';
	if(g->clic_y < g->x - 1 && g->clic_x > 0 )
		g->map[g->clic_x - 1][g->clic_y + 1] = 'L';
	while(i < bmb)
	{
		x = rand()% g->x +0;
		y = rand()% g->x +0;
		if(g->map_min[x][y] == 'X' || g->map[x][y] == 'L')
			continue ;
		g->map_min[x][y] = 'X';
		i++;
	}
	//ft_print_map(g, g->map_min);
}

int is_l(t_gen *g)
{
	int x;
	int y;

	x = 0;
	while(x < g->x)
	{
		y = 0;
		while(y < g->x)
		{
			if(g->map[x][y] == 'L')
				return(1);
			y++;
		}
		x++;
	}
	return(0);
}

int ft_nozero(char c)
{
	if(c > '0' && c <= '9')
		return(1);
	return(0);
}

char **ft_edit_tab(int i, t_gen *g)
{
	int x;
	int y;
	char **tab;

	tab = malloc(sizeof(char *) * (i + 1));
	x = 0;
	while(x < i)
	{
		y = 0;
		tab[x] = malloc(sizeof(char) * (i + 1));
		while(y < i)
		{
			tab[x][y] = 'x';
			y++;
		}
		tab[x][y] = 0;
		x++;
	}
	tab[x] = NULL;
	return(tab);
}

int ft_check_link(t_gen *g, int x_t, int y_t)
{
	char **tab = ft_edit_tab(g->x, g);
	int y;
	int x;
	int sorti;

	tab[x_t][y_t] = 'o';

	sorti = 1;
	while(sorti == 1)
	{
		sorti = 0;
		x = 0;
		while(x < g->x)
		{
			y = 0;
			while(y < g->x)
			{
				if(tab[x][y] == 'x' && x > 0 && tab[x - 1][y] == 'o' && g->map[x - 1][y] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && y > 0 && tab[x][y - 1] == 'o' && g->map[x][y - 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}

				if(tab[x][y] == 'x' && x < g->x - 1 && tab[x + 1][y] == 'o' && g->map[x + 1][y] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && y < g->x - 1 && tab[x][y + 1] == 'o' && g->map[x][y + 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && x > 0 && y > 0 && tab[x - 1][y - 1] == 'o' && g->map[x - 1][y - 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && x < g->x - 1 && y < g->x - 1 && tab[x + 1][y + 1] == 'o' && g->map[x + 1][y + 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}

				if(tab[x][y] == 'x' && x < g->x - 1 && y > 0 && tab[x + 1][y - 1] == 'o' && g->map[x + 1][y - 1] == '0')
				{
					tab[x ][y ] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && x > 0 && y < g->x - 1 && tab[x - 1][y + 1] == 'o' && g->map[x - 1][y + 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				y++;
			}
			x++;
		}

	}

	if(tab[g->clic_x][g->clic_y] == 'o')
		return(1);
	return(0);
}

int ft_check_link_f(t_gen *g, int x_t, int y_t)
{
	char **tab = ft_edit_tab(g->x, g);
	int y;
	int x;
	int sorti;

	tab[x_t][y_t] = 'o';

	sorti = 1;
	while(sorti == 1)
	{
		sorti = 0;
		x = 0;
		while(x < g->x)
		{
			y = 0;
			while(y < g->x)
			{
				if(tab[x][y] == 'x' && x > 0 && tab[x - 1][y] == 'o' && g->map[x - 1][y] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && y > 0 && tab[x][y - 1] == 'o' && g->map[x][y - 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}

				if(tab[x][y] == 'x' && x < g->x - 1 && tab[x + 1][y] == 'o' && g->map[x + 1][y] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && y < g->x - 1 && tab[x][y + 1] == 'o' && g->map[x][y + 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && x > 0 && y > 0 && tab[x - 1][y - 1] == 'o' && g->map[x - 1][y - 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && x < g->x - 1 && y < g->x - 1 && tab[x + 1][y + 1] == 'o' && g->map[x + 1][y + 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}

				if(tab[x][y] == 'x' && x < g->x - 1 && y > 0 && tab[x + 1][y - 1] == 'o' && g->map[x + 1][y - 1] == '0')
				{
					tab[x ][y ] = 'o';
					sorti = 1;
				}
				if(tab[x][y] == 'x' && x > 0 && y < g->x - 1 && tab[x - 1][y + 1] == 'o' && g->map[x - 1][y + 1] == '0')
				{
					tab[x][y] = 'o';
					sorti = 1;
				}
				y++;
			}
			x++;
		}

	}

	if(tab[g->clic_x_f][g->clic_y_f] == 'o')
		return(1);
	return(0);
}

void ft_isconnect(t_gen *g)
{
	int x;
	int y;

	x = 0;
	while(x < g->x)
	{
		y = 0;
		while(y < g->x)
		{
			if(g->map[x][y] == '0' && g->map_0[x][y] == '1' && ft_check_link_f(g, x, y))
			{
				g->map_0[x][y] = '0';
			}
			else if (g->map[x][y] == '0' && g->map_0[x][y] == '1' && !ft_check_link_f(g, x, y))
			{
				g->map[x][y] = '*';
			}
			y++;
		}
		x++;
	}
}

int ft_count_bmb(t_gen *g, int x, int y)
{
	int i;

	i = 0;
	if(x > 0 && g->map_min[x - 1][y] == 'X')
		i++;
	if(y > 0 && g->map_min[x][y - 1] == 'X')
		i++;
	if(x < g->x - 1 && g->map_min[x + 1][y] == 'X')
		i++;
	if(y < g->x - 1 && g->map_min[x][y + 1] == 'X')
		i++;

	if(x > 0 && y > 0 && g->map_min[x - 1][y - 1] == 'X')
		i++;
	if(x < g->x - 1 && y < g->x - 1 && g->map_min[x + 1][y + 1] == 'X')
		i++;
	if(x < g->x - 1 && y > 0 && g->map_min[x + 1][y - 1] == 'X')
		i++;
	if(y < g->x - 1 && x > 0 && g->map_min[x - 1][y + 1] == 'X')
		i++;

	return(i);
}

void ft_chr_bmb(t_gen *g)
{
	int x;
	int y;
	int count_bmb;
	int flag;

	flag = 0;
	while(flag == 0 || is_l(g))
	{
		flag = 1;
		x = 0;
		while(x < g->x)
		{
			y = -1;
			while(++y < g->x)
			{
				if(g->map[x][y] == 'L')
				{

					/*if(ft_count_bmb(g, x, y) == 0)
					  {
					  if(x > 0 && ft_check_link_f(g, x-1, y) == 0)
					  g->map[x][y] = '*';
					  if(y > 0 && ft_check_link_f(g, x, y - 1) == 0)
					  g->map[x][y] = '*';
					  if(x < g->x - 1 && ft_check_link_f(g, x+1, y) == 0)
					  g->map[x][y] = '*';
					  if(y < g->x - 1 && ft_check_link_f(g, x, y + 1) == 0)
					  g->map[x][y] = '*';

					  if(x > 0 && y > 0 && ft_check_link_f(g, x-1, y - 1) == 0)
					  g->map[x][y] = '*';
					  if(x < g->x - 1 && y < g->x - 1 && ft_check_link_f(g, x + 1, y + 1) == 0)
					  g->map[x][y] = '*';


					  if(x > 0 && y < g->x - 1 && ft_check_link_f(g, x - 1, y + 1) == 0)
					  g->map[x][y] = '*';

					  if(y > 0 && x < g->x - 1 && ft_check_link_f(g, x + 1, y - 1) == 0)
					  g->map[x][y] = '*';
					  if(g->map[x][y] == '*')
					  continue ;
					  }*/




					count_bmb = 0;
					if(x > 0 && g->map_min[x - 1][y] == 'X')
						count_bmb++;
					else if(x > 0 && g->map_min[x - 1][y] != 'X' && g->map[x - 1][y] == '*')
						g->map[x - 1][y] = 'L';

					if(x < g->x - 1 && g->map_min[x + 1][y] == 'X')
						count_bmb++;
					else if (x < g->x - 1 && g->map_min[x + 1][y] != 'X' && g->map[x + 1][y] == '*')
						g->map[x + 1][y] = 'L';

					if(y > 0 && g->map_min[x][y - 1] == 'X')
						count_bmb++;
					else if(y > 0 && g->map_min[x][y - 1] != 'X' && g->map[x][y - 1] == '*')
						g->map[x][y - 1] = 'L';

					if(y < g->x - 1 && g->map_min[x][y + 1] == 'X')
						count_bmb++;
					else if(y < g->x - 1 && g->map_min[x][y + 1] != 'X' && g->map[x][y + 1] == '*')
						g->map[x][y + 1] = 'L';

					if(x > 0 && y > 0 && g->map_min[x - 1][y - 1] == 'X')
						count_bmb++;
					else if (x > 0 && y > 0 && g->map_min[x - 1][y - 1] != 'X' && g->map[x - 1][y - 1] == '*')
						g->map[x - 1][y - 1] = 'L';

					if(x < g->x - 1 &&  y < g->x - 1 && g->map_min[x + 1][y + 1] == 'X')
						count_bmb++;
					else if(x < g->x - 1 &&  y < g->x - 1 && g->map_min[x + 1][y + 1] != 'X' && g->map[x + 1][y + 1] == '*')
						g->map[x + 1][y + 1] = 'L';

					if(y > 0 && x < g->x - 1 && g->map_min[x + 1][y - 1] == 'X')
						count_bmb++;
					else if(y > 0 && x < g->x - 1 && g->map_min[x + 1][y - 1] != 'X' && g->map[x + 1][y - 1] == '*')
						g->map[x + 1][y - 1] = 'L';

					if(y < g->x - 1 && x > 0 && g->map_min[x - 1][y + 1] == 'X')
						count_bmb++;
					else if (y < g->x - 1 && x > 0 && g->map_min[x - 1][y + 1] != 'X' && g->map[x - 1][y + 1] == '*')
						g->map[x - 1][y + 1] = 'L';

					if (count_bmb != 0)
					{}
					else
						flag = 0;


					g->map[x][y] = count_bmb + 48;

				}
			}
			x++;
		}
	}
}

void ft_filtre(t_gen *g)
{
	int x;
	int y;

	x = 0;
	g->clic[g->clic_x][g->clic_y] = '1';
	while(x < g->x)
	{
		y = 0;
		while(y < g->x)
		{
			if(g->map[x][y] == '0')
			{
				g->clic[x][y] = '1';
			}
			else if (g->map[x][y] != '*' && ((x > 0 && g->map[x - 1][y] == '0') || (y > 0 && g->map[x][y - 1] == '0') || (x < g->x - 1 && g->map[x + 1][y] == '0') || (y < g->x - 1 && g->map[x][y + 1] == '0') ||
						(x > 0 && y > 0 && g->map[x - 1][y - 1] == '0') || (y < g->x - 1 && x < g->x - 1 && g->map[x + 1][y + 1] == '0') ||
						(y > 0 && x < g->x - 1 && g->map[x + 1][y - 1] == '0') || (x > 0 && y < g->x - 1 && g->map[x - 1][y + 1] == '0')     ))
			{
				g->clic[x][y] = '1';
			}
			else if (g->clic[x][y] != '1')
				g->map[x][y] = '*';


			y++;
		}
		x++;
	}
}

void ft_zero(t_gen *g)
{
	int x;
	int y;
	int s;

	s = 1;
	while(s == 1)
	{
		s = 0;
		x = 0;
		while(x < g->x)
		{
			y = 0;
			while(y < g->x)
			{
				if(g->map[x][y] == '0')
				{
					if(x > 0 && g->map[x - 1][y] == '*')
					{
						g->map[x - 1][y] = ft_count_bmb(g, x - 1, y) + 48;
						s = 1;
					}
					if(y > 0 && g->map[x][y - 1] == '*')
					{
						g->map[x][y - 1] = ft_count_bmb(g, x, y - 1) + 48;
						s = 1;
					}

					if(x < g->x -1 && g->map[x + 1][y] == '*')
					{
						g->map[x + 1][y] = ft_count_bmb(g, x + 1, y) + 48;
						s = 1;
					}
					if(y < g->x - 1 && g->map[x][y + 1] == '*')
					{
						g->map[x][y + 1] = ft_count_bmb(g, x, y + 1) + 48;
						s = 1;
					}


					if(x > 0 && y > 0 && g->map[x - 1][y - 1] == '*')
					{
						g->map[x - 1][y - 1] = ft_count_bmb(g, x - 1, y - 1) + 48;
						s = 1;
					}
					if(x < g->x -1 && y < g->x - 1 && g->map[x + 1][y + 1] == '*')
					{
						g->map[x + 1][y + 1] = ft_count_bmb(g, x + 1, y + 1) + 48;
						s = 1;
					}

					if(x < g->x -1 && y > 0 && g->map[x + 1][y - 1] == '*')
					{
						g->map[x + 1][y - 1] = ft_count_bmb(g, x + 1, y - 1) + 48;
						s = 1;
					}
					if(y < g->x - 1 && x > 0 && g->map[x - 1][y + 1] == '*')
					{
						g->map[x - 1][y + 1] = ft_count_bmb(g, x - 1, y + 1) + 48;
						s = 1;
					}
				}
				y++;
			}
			x++;
		}
	}
}

int ft_win(t_gen *g)
{
	int x;
	int y;
	int cnt;

	x = 0;
	while(x < g->x)
	{
		y = 0;
		while(y < g->x)
		{
			if(g->map[x][y] == '*' && g->map_min[x][y] == 'X')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

void ft_revel(t_gen *g)
{
	static int  first = 0;

	if(first == 0)
	{
		ft_rand(g);
		g->clic_y_f = g->clic_y;
		g->clic_x_f = g->clic_x;
	}
	if(g->perdu >= 1)
		exit(0);
	if(g->map_min[g->clic_x][g->clic_y] == 'X')
	{
		ft_putstr("game_over\n");
		g->perdu++;
		return;
	}
	g->map[g->clic_x][g->clic_y] = 'L';
	if(ft_count_bmb(g, g->clic_x, g->clic_y) == 0)
		g->map_0[g->clic_x][g->clic_y] = '0';
	ft_chr_bmb(g);
	ft_isconnect(g);
	ft_filtre(g);
	ft_zero(g);

	/*if(ft_win(g) == 0)
	{
		g->perdu++;
		ft_putstr("GG");
		
	}*/
	//vire ceu qui ne sont pas 'clique' || pas conecter au 0





	ft_print_map(g, g->map);

	first = 1;
}

int ft_mouse(int button, int x,int y, t_gen *g)
{
	ft_chr_clic(x, y, g);
	if(ft_isalnum(g->map[g->clic_x][g->clic_y]))
		return(0);
	printf("%d\n", button);
	if(button == 1 && g->drap[g->clic_x][g->clic_y] != '!')
		ft_revel(g);
	if(button == 2 && g->map[g->clic_x][g->clic_y] == '*')
		ft_drap(g);
	ft_draw_map(g);
	return(0);
}

int		key_pressed(int kc, t_gen *g)
{
	if(kc == 53)
		exit(0);
	return(0);
}
