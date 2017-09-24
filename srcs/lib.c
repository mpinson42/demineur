/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:07:01 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 19:07:03 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dem.h"

int		is_l(t_gen *g)
{
	int x;
	int y;

	x = 0;
	while (x < g->x)
	{
		y = 0;
		while (y < g->x)
		{
			if (g->map[x][y] == 'L')
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

int		ft_nozero(char c)
{
	if (c > '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_drap(t_gen *g)
{
	if (g->drap[g->clic_x][g->clic_y] == '!')
		g->drap[g->clic_x][g->clic_y] = '.';
	else if (g->drap[g->clic_x][g->clic_y] == '.')
		g->drap[g->clic_x][g->clic_y] = '!';
}

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
