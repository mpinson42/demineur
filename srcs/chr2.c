/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:10:34 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 19:10:36 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dem.h"

int		ft_chr_x_2(t_gen *g, int x, int y, int count_bmb)
{
	if (x > 0 && y > 0 && g->map_min[x - 1][y - 1] == 'X')
		count_bmb++;
	else if (x > 0 && y > 0 &&
		g->map_min[x - 1][y - 1] != 'X' && g->map[x - 1][y - 1] == '*')
		g->map[x - 1][y - 1] = 'L';
	if (x < g->x - 1 && y < g->x - 1 && g->map_min[x + 1][y + 1] == 'X')
		count_bmb++;
	else if (x < g->x - 1 && y < g->x - 1 &&
		g->map_min[x + 1][y + 1] != 'X' && g->map[x + 1][y + 1] == '*')
		g->map[x + 1][y + 1] = 'L';
	if (y > 0 && x < g->x - 1 && g->map_min[x + 1][y - 1] == 'X')
		count_bmb++;
	else if (y > 0 && x < g->x - 1 &&
		g->map_min[x + 1][y - 1] != 'X' && g->map[x + 1][y - 1] == '*')
		g->map[x + 1][y - 1] = 'L';
	if (y < g->x - 1 && x > 0 && g->map_min[x - 1][y + 1] == 'X')
		count_bmb++;
	else if (y < g->x - 1 && x > 0 &&
		g->map_min[x - 1][y + 1] != 'X' && g->map[x - 1][y + 1] == '*')
		g->map[x - 1][y + 1] = 'L';
	g->map[x][y] = count_bmb + 48;
	return (count_bmb);
}

int		ft_chr_x(t_gen *g, int x, int y)
{
	int count_bmb;

	count_bmb = 0;
	if (x > 0 && g->map_min[x - 1][y] == 'X')
		count_bmb++;
	else if (x > 0 &&
		g->map_min[x - 1][y] != 'X' && g->map[x - 1][y] == '*')
		g->map[x - 1][y] = 'L';
	if (x < g->x - 1 && g->map_min[x + 1][y] == 'X')
		count_bmb++;
	else if (x < g->x - 1 &&
		g->map_min[x + 1][y] != 'X' && g->map[x + 1][y] == '*')
		g->map[x + 1][y] = 'L';
	if (y > 0 && g->map_min[x][y - 1] == 'X')
		count_bmb++;
	else if (y > 0 &&
		g->map_min[x][y - 1] != 'X' && g->map[x][y - 1] == '*')
		g->map[x][y - 1] = 'L';
	if (y < g->x - 1 && g->map_min[x][y + 1] == 'X')
		count_bmb++;
	else if (y < g->x - 1 &&
		g->map_min[x][y + 1] != 'X' && g->map[x][y + 1] == '*')
		g->map[x][y + 1] = 'L';
	return (ft_chr_x_2(g, x, y, count_bmb));
}

void	ft_chr_bmb(t_gen *g)
{
	int x;
	int y;
	int count_bmb;
	int flag;

	flag = 0;
	while (flag == 0 || is_l(g))
	{
		flag = 1;
		x = -1;
		while (++x < g->x)
		{
			y = -1;
			while (++y < g->x)
			{
				if (g->map[x][y] == 'L')
				{
					if (ft_chr_x(g, x, y) == 0)
						flag = 0;
				}
			}
		}
	}
}

void	ft_chr_walcard2(t_gen *g, int x, int y, int *s)
{
	if (x > 0 && g->map[x - 1][y] == '*')
	{
		g->map[x - 1][y] = ft_count_bmb(g, x - 1, y) + 48;
		s[0] = 1;
	}
	if (y > 0 && g->map[x][y - 1] == '*')
	{
		g->map[x][y - 1] = ft_count_bmb(g, x, y - 1) + 48;
		s[0] = 1;
	}
	if (x < g->x - 1 && g->map[x + 1][y] == '*')
	{
		g->map[x + 1][y] = ft_count_bmb(g, x + 1, y) + 48;
		s[0] = 1;
	}
	if (y < g->x - 1 && g->map[x][y + 1] == '*')
	{
		g->map[x][y + 1] = ft_count_bmb(g, x, y + 1) + 48;
		s[0] = 1;
	}
	if (x > 0 && y > 0 && g->map[x - 1][y - 1] == '*')
	{
		g->map[x - 1][y - 1] = ft_count_bmb(g, x - 1, y - 1) + 48;
		s[0] = 1;
	}
}

void	ft_chr_walcard(t_gen *g, int x, int y, int *s)
{
	if (x < g->x - 1 && y < g->x - 1 && g->map[x + 1][y + 1] == '*')
	{
		g->map[x + 1][y + 1] = ft_count_bmb(g, x + 1, y + 1) + 48;
		s[0] = 1;
	}
	if (x < g->x - 1 && y > 0 && g->map[x + 1][y - 1] == '*')
	{
		g->map[x + 1][y - 1] = ft_count_bmb(g, x + 1, y - 1) + 48;
		s[0] = 1;
	}
	if (y < g->x - 1 && x > 0 && g->map[x - 1][y + 1] == '*')
	{
		g->map[x - 1][y + 1] = ft_count_bmb(g, x - 1, y + 1) + 48;
		s[0] = 1;
	}
	ft_chr_walcard2(g, x, y, s);
}
