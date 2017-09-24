/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:06:54 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 19:06:55 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dem.h"

int		red_cross(t_gen *g)
{
	(void)g;
	system("killall afplay");
	exit(0);
	return (0);
}

void	ft_revel2(t_gen *g, int first)
{
	if (first == 0)
	{
		ft_rand(g);
		g->clic_y_f = g->clic_y;
		g->clic_x_f = g->clic_x;
	}
	if (g->perdu >= 1)
	{
		system("killall afplay");
		exit(0);
	}
	if (g->map_min[g->clic_x][g->clic_y] == 'X')
	{
		g->map[g->clic_x][g->clic_y] = '\n';
		system("afplay musique/destruction.mp3 &");
		ft_putstr("game_over\n");
		g->perdu++;
		return ;
	}
}

void	ft_revel(t_gen *g)
{
	static int first = 0;

	g->map[g->clic_x][g->clic_y] = 'L';
	ft_revel2(g, first);
	if (ft_count_bmb(g, g->clic_x, g->clic_y) == 0)
		g->map_0[g->clic_x][g->clic_y] = '0';
	ft_chr_bmb(g);
	ft_isconnect(g);
	ft_filtre(g);
	ft_zero(g);
	first = 1;
}

int		ft_mouse(int button, int x, int y, t_gen *g)
{
	ft_chr_clic(x, y, g);
	if (ft_isalnum(g->map[g->clic_x][g->clic_y]))
		return (0);
	if (button == 1 && g->drap[g->clic_x][g->clic_y] != '!')
		ft_revel(g);
	if (button == 2 && g->map[g->clic_x][g->clic_y] == '*')
		ft_drap(g);
	ft_draw_map(g);
	return (0);
}

int		key_pressed(int kc, t_gen *g)
{
	if (kc == 53)
	{
		system("killall afplay");
		exit(0);
	}
	return (0);
}
