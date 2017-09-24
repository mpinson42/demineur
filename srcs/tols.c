/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tols.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:13:34 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 19:13:36 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dem.h"

void	ft_init_clic(t_gen *g)
{
	g->map[g->clic_x][g->clic_y] = 'L';
	if (g->clic_x > 0)
		g->map[g->clic_x - 1][g->clic_y] = 'L';
	if (g->clic_x < g->x - 1)
		g->map[g->clic_x + 1][g->clic_y] = 'L';
	if (g->clic_y > 0)
		g->map[g->clic_x][g->clic_y - 1] = 'L';
	if (g->clic_y < g->x - 1)
		g->map[g->clic_x][g->clic_y + 1] = 'L';
	if (g->clic_x > 0 && g->clic_y > 0)
		g->map[g->clic_x - 1][g->clic_y - 1] = 'L';
	if (g->clic_x < g->x - 1 && g->clic_y < g->x - 1)
		g->map[g->clic_x + 1][g->clic_y + 1] = 'L';
	if (g->clic_y > 0 && g->clic_x < g->x - 1)
		g->map[g->clic_x + 1][g->clic_y - 1] = 'L';
	if (g->clic_y < g->x - 1 && g->clic_x > 0)
		g->map[g->clic_x - 1][g->clic_y + 1] = 'L';
}

void	ft_rand(t_gen *g)
{
	int bmb;
	int x;
	int y;
	int i;

	bmb = 10;
	if (g->argc >= 3)
		bmb = ft_atoi(g->argv[2]);
	if (bmb < 10 || bmb > g->x * g->x - 9)
		bmb = 10;
	g->bmb = bmb;
	srand(time(NULL));
	ft_init_clic(g);
	i = -1;
	while (++i < bmb)
	{
		x = rand() % g->x + 0;
		y = rand() % g->x + 0;
		if (g->map_min[x][y] == 'X' || g->map[x][y] == 'L')
			continue ;
		g->map_min[x][y] = 'X';
	}
}

char	**ft_edit_tab(int i, t_gen *g)
{
	int		x;
	int		y;
	char	**tab;

	tab = malloc(sizeof(char *) * (i + 1));
	x = 0;
	while (x < i)
	{
		y = 0;
		tab[x] = malloc(sizeof(char) * (i + 1));
		while (y < i)
		{
			tab[x][y] = 'x';
			y++;
		}
		tab[x][y] = 0;
		x++;
	}
	tab[x] = NULL;
	return (tab);
}

int		ft_win_2(t_gen *g)
{
	int x;
	int y;

	x = 0;
	while (x < g->x)
	{
		y = 0;
		while (y < g->x)
		{
			if (g->map[x][y] == '*' && g->map_min[x][y] != 'X')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}
