/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 17:24:16 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 18:31:16 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dem.h"

void	ft_isconnect(t_gen *g)
{
	int x;
	int y;

	x = 0;
	while (x < g->x)
	{
		y = 0;
		while (y < g->x)
		{
			if (g->map[x][y] == '0' && g->map_0[x][y] == '1' &&
					ft_check_link_f(g, x, y))
				g->map_0[x][y] = '0';
			else if (g->map[x][y] == '0' && g->map_0[x][y] == '1' &&
					!ft_check_link_f(g, x, y))
				g->map[x][y] = '*';
			y++;
		}
		x++;
	}
}

int		ft_count_bmb(t_gen *g, int x, int y)
{
	int i;

	i = 0;
	if (x > 0 && g->map_min[x - 1][y] == 'X')
		i++;
	if (y > 0 && g->map_min[x][y - 1] == 'X')
		i++;
	if (x < g->x - 1 && g->map_min[x + 1][y] == 'X')
		i++;
	if (y < g->x - 1 && g->map_min[x][y + 1] == 'X')
		i++;
	if (x > 0 && y > 0 && g->map_min[x - 1][y - 1] == 'X')
		i++;
	if (x < g->x - 1 && y < g->x - 1 && g->map_min[x + 1][y + 1] == 'X')
		i++;
	if (x < g->x - 1 && y > 0 && g->map_min[x + 1][y - 1] == 'X')
		i++;
	if (y < g->x - 1 && x > 0 && g->map_min[x - 1][y + 1] == 'X')
		i++;
	return (i);
}

void	ft_filtre(t_gen *g)
{
	int x;
	int y;

	x = -1;
	g->clic[g->clic_x][g->clic_y] = '1';
	while (++x < g->x)
	{
		y = -1;
		while (++y < g->x)
		{
			if (g->map[x][y] == '0')
				g->clic[x][y] = '1';
			else if (g->map[x][y] != '*' && ((x > 0 && g->map[x - 1][y] == '0')
				|| (y > 0 && g->map[x][y - 1] == '0') || (x < g->x - 1 &&
					g->map[x + 1][y] == '0') || (y < g->x - 1 &&
					g->map[x][y + 1] == '0') || (x > 0 && y > 0 &&
					g->map[x - 1][y - 1] == '0') || (y < g->x - 1 &&
					x < g->x - 1 && g->map[x + 1][y + 1] == '0') ||
					(y > 0 && x < g->x - 1 && g->map[x + 1][y - 1] == '0') ||
					(x > 0 && y < g->x - 1 && g->map[x - 1][y + 1] == '0')))
				g->clic[x][y] = '1';
			else if (g->clic[x][y] != '1')
				g->map[x][y] = '*';
		}
	}
}

void	ft_zero(t_gen *g)
{
	int x;
	int y;
	int s;

	s = 1;
	while (s == 1)
	{
		s = 0;
		x = -1;
		while (++x < g->x)
		{
			y = -1;
			while (++y < g->x)
			{
				if (g->map[x][y] == '0')
					ft_chr_walcard(g, x, y, &s);
			}
		}
	}
}

int		ft_win(t_gen *g)
{
	int x;
	int y;
	int cnt;

	x = 0;
	while (x < g->x)
	{
		y = 0;
		while (y < g->x)
		{
			if (g->map[x][y] == '*' && g->map_min[x][y] == 'X')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}
