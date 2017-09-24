/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 16:40:51 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 17:14:50 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dem.h"

int		ft_init_map(t_gen *g, int x, int y)
{
	while (++x < g->x)
	{
		y = -1;
		g->map_min[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		g->map[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		g->map_0[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		g->clic[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		g->drap[x] = (char *)malloc(sizeof(char) * (g->x + 1));
		if (g->map[x] == NULL || g->map_min[x] == NULL || g->map_0[x] == NULL
				|| g->clic[x] == NULL || g->drap[x] == NULL)
			return (-1);
		while (++y < g->x)
		{
			g->map_min[x][y] = '.';
			g->map[x][y] = '*';
			g->map_0[x][y] = '1';
			g->clic[x][y] = '0';
			g->drap[x][y] = '.';
		}
		g->map_min[x][y] = 0;
		g->map[x][y] = 0;
	}
	g->map_min[x] = NULL;
	g->map[x] = NULL;
	return (0);
}

int		ft_init(t_gen *g, int argc, char **argv)
{
	int x;
	int y;

	g->x = 10;
	if (argc >= 2)
		g->x = ft_atoi(argv[1]);
	if (g->x < 10 || g->x > 45)
		g->x = 10;
	if (argc >= 3 && (ft_atoi(argv[2]) < 10 ||
				ft_atoi(argv[2]) > g->x * g->x - 9))
		g->bmb = 10;
	else if (argc >= 3)
		g->bmb = ft_atoi(argv[2]);
	g->map = (char **)malloc(sizeof(char *) * (g->x + 1));
	g->map_min = (char **)malloc(sizeof(char *) * (g->x + 1));
	g->map_0 = (char **)malloc(sizeof(char *) * (g->x + 1));
	g->clic = (char **)malloc(sizeof(char *) * (g->x + 1));
	g->drap = (char **)malloc(sizeof(char *) * (g->x + 1));
	if (g->x < 10 || g->map == NULL || g->map_min == NULL || g->map_0 == NULL
			|| g->clic == NULL || g->drap == NULL)
		return (-1);
	if (ft_init_map(g, -1, y) == -1)
		return (-1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_gen g;

	ft_bzero(&g, sizeof(g));
	ft_init(&g, argc, argv);
	g.argv = argv;
	g.argc = argc;
	system("afplay musique/sao.mp3 &");
	if (!(g.mlx = mlx_init()))
		return (-1);
	if (!(g.img = mlx_new_image(g.mlx, W, H)))
		return (-1);
	if (!(g.img_ptr = mlx_get_data_addr(g.img, &(g.bpp),
					&(g.s_l), &(g.endian))))
		return (-1);
	if (!(g.win = mlx_new_window(g.mlx, W, H, "demineur")))
		return (-1);
	ft_draw_map(&g);
	mlx_mouse_hook(g.win, &ft_mouse, &g);
	mlx_hook(g.win, 17, (1L << 17), &red_cross, &g);
	mlx_hook(g.win, 2, 1L << 0, &key_pressed, &g);
	mlx_loop(g.mlx);
}
