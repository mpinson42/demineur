/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 17:45:23 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 17:55:40 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dem.h"

void	ft_chr_clic(int x, int y, t_gen *g)
{
	int espace;
	int count;
	int test;

	espace = H / g->x;
	count = 0;
	test = 0;
	while (test < H)
	{
		if (x > test && x <= test + espace)
			g->clic_x = count;
		if (y > test && y <= test + espace)
			g->clic_y = count;
		test += espace;
		count++;
	}
}

void	ft_check_chr_0_2(t_gen *g, int x, int y, int *sorti)
{
	if (g->tab[x][y] == 'x' && x > 0 &&
			g->tab[x - 1][y] == 'o' && g->map[x - 1][y] == '0')
	{
		g->tab[x][y] = 'o';
		sorti[0] = 1;
	}
	if (g->tab[x][y] == 'x' && y > 0 &&
			g->tab[x][y - 1] == 'o' && g->map[x][y - 1] == '0')
	{
		g->tab[x][y] = 'o';
		sorti[0] = 1;
	}
	if (g->tab[x][y] == 'x' && x < g->x - 1 &&
			g->tab[x + 1][y] == 'o' && g->map[x + 1][y] == '0')
	{
		g->tab[x][y] = 'o';
		sorti[0] = 1;
	}
	if (g->tab[x][y] == 'x' && y < g->x - 1 &&
			g->tab[x][y + 1] == 'o' && g->map[x][y + 1] == '0')
	{
		g->tab[x][y] = 'o';
		sorti[0] = 1;
	}
}

void	ft_check_chr_0(t_gen *g, int x, int y, int *sorti)
{
	if (g->tab[x][y] == 'x' && x > 0 && y > 0 &&
			g->tab[x - 1][y - 1] == 'o' && g->map[x - 1][y - 1] == '0')
	{
		g->tab[x][y] = 'o';
		sorti[0] = 1;
	}
	if (g->tab[x][y] == 'x' && x < g->x - 1 && y < g->x - 1 &&
			g->tab[x + 1][y + 1] == 'o' && g->map[x + 1][y + 1] == '0')
	{
		g->tab[x][y] = 'o';
		sorti[0] = 1;
	}
	if (g->tab[x][y] == 'x' && x < g->x - 1 && y > 0 &&
			g->tab[x + 1][y - 1] == 'o' && g->map[x + 1][y - 1] == '0')
	{
		g->tab[x][y] = 'o';
		sorti[0] = 1;
	}
	if (g->tab[x][y] == 'x' && x > 0 && y < g->x - 1 &&
			g->tab[x - 1][y + 1] == 'o' && g->map[x - 1][y + 1] == '0')
	{
		g->tab[x][y] = 'o';
		sorti[0] = 1;
	}
	ft_check_chr_0_2(g, x, y, sorti);
}

int		ft_check_link(t_gen *g, int x_t, int y_t)
{
	int		y;
	int		x;
	int		sorti;

	g->tab = ft_edit_tab(g->x, g);
	g->tab[x_t][y_t] = 'o';
	sorti = 1;
	while (sorti == 1)
	{
		sorti = 0;
		x = -1;
		while (++x < g->x)
		{
			y = -1;
			while (++y < g->x)
				ft_check_chr_0(g, x, y, &sorti);
		}
	}
	if (g->tab[g->clic_x][g->clic_y] == 'o')
	{
		ft_free_tab(g->tab);
		return (1);
	}
	ft_free_tab(g->tab);
	return (0);
}

int		ft_check_link_f(t_gen *g, int x_t, int y_t)
{
	int		y;
	int		x;
	int		sorti;

	g->tab = ft_edit_tab(g->x, g);
	g->tab[x_t][y_t] = 'o';
	sorti = 1;
	while (sorti == 1)
	{
		sorti = 0;
		x = -1;
		while (++x < g->x)
		{
			y = -1;
			while (++y < g->x)
				ft_check_chr_0(g, x, y, &sorti);
		}
	}
	if (g->tab[g->clic_x_f][g->clic_y_f] == 'o')
	{
		ft_free_tab(g->tab);
		return (1);
	}
	ft_free_tab(g->tab);
	return (0);
}
