/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 18:54:20 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/24 18:54:23 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEM_H
# define DEM_H

# include "libft.h"
# include "mlx.h"
# include <time.h>

# define W 1080
# define H 1080

typedef	struct		s_gen
{
	char			**map;
	char			**map_min;
	char			**map_0;
	char			**clic;
	char			**drap;
	char			**argv;
	char			**tab;
	int				argc;
	int				bmb;
	int				perdu;
	void			*win;
	void			*mlx;
	void			*img;
	int				bpp;
	int				s_l;
	int				endian;
	int				red;
	int				blue;
	int				green;
	int				clic_x;
	int				clic_y;
	int				clic_x_f;
	int				clic_y_f;
	int				save_x;
	int				save_y;
	int				lang;
	char			*img_ptr;
	int				x;
	int				y;
}					t_gen;

int					ft_mouse(int button, int x, int y, t_gen *g);
int					red_cross(t_gen *g);
int					key_pressed(int kc, t_gen *g);
void				ft_draw_map(t_gen *g);
int					is_l(t_gen *g);
int					ft_check_link_f(t_gen *g, int x_t, int y_t);
void				ft_drap(t_gen *g);
void				ft_rand(t_gen *g);
void				ft_chr_clic(int x, int y, t_gen *g);
int					ft_count_bmb(t_gen *g, int x, int y);
void				ft_isconnect(t_gen *g);
void				ft_filtre(t_gen *g);
void				ft_zero(t_gen *g);
void				ft_chr_bmb(t_gen *g);
void				ft_chr_walcard(t_gen *g, int x, int y, int *s);
char				**ft_edit_tab(int i, t_gen *g);
void				ft_free_tab(char **tab);
int					ft_win_2(t_gen *g);
#endif
