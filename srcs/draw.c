/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 18:57:55 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 18:57:59 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_draw_grille(int x, int y, t_gen *g)
{
	int i;

	g->red = 255 / 2;
	g->blue = 255 / 2;
	g->green = 255 / 2;
	i = 0;
	while (i < H)
	{
		ft_putpixel_in_img(x, i, g, 42);
		i++;
	}
	i = 0;
	while (i < H)
	{
		ft_putpixel_in_img(i, y, g, 42);
		i++;
	}
}

void	ft_chois_color(t_gen *g, int x, int y)
{
	if (g->map_min[x][y] == 'X' && g->perdu == 1)
	{
		g->red = 255;
		g->blue = 0;
		g->green = 0;
	}
	else if (g->map[x][y] == '*')
	{
		g->red = 0;
		g->blue = 255;
		g->green = 0;
	}
	else if (g->map[x][y] == '0' || g->map[x][y] == '-')
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
}

void	draw_chiffre(t_gen *g, int x, int y, char c[2])
{
	while (++x < g->x)
	{
		y = -1;
		while (++y < g->x)
		{
			g->save_x = x * g->lang;
			g->save_y = y * g->lang;
			if (g->map[x][y] == '*' && g->drap[x][y] == '!')
				mlx_string_put(g->mlx, g->win, g->save_x + g->lang / 2,
						g->save_y + g->lang / 2, 0x00FF0000, "!");
			if (ft_isalnum(g->map[x][y]))
			{
				c[0] = g->map[x][y];
				c[1] = 0;
				if (g->map[x][y] == '0')
					mlx_string_put(g->mlx, g->win, g->save_x + g->lang / 2,
							g->save_y + g->lang / 2, 0x00000000, c);
				else
					mlx_string_put(g->mlx, g->win, g->save_x + g->lang / 2,
							g->save_y + g->lang / 2, 0x00FFFFFF, c);
			}
		}
	}
}

void	ft_draw_map(t_gen *g)
{
	int		x;
	int		y;
	char	c[2];

	x = -1;
	g->lang = H / g->x;
	while (++x < g->x)
	{
		y = -1;
		while (++y < g->x)
		{
			ft_chois_color(g, x, y);
			g->save_x = x * g->lang - 1;
			while (++g->save_x < (x + 1) * g->lang)
			{
				g->save_y = y * g->lang - 1;
				while (++g->save_y < (y + 1) * g->lang)
					ft_putpixel_in_img(g->save_x, g->save_y, g, 42);
			}
			ft_draw_grille(x * g->lang, y * g->lang, g);
		}
	}
	ft_draw_grille(x * g->lang - 1, y * g->lang - 1, g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	draw_chiffre(g, -1, y, c);
}
