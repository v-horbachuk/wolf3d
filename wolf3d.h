/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:47:30 by vhorbach          #+#    #+#             */
/*   Updated: 2017/05/19 15:47:34 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIN_WID 900
# define WIN_HIGH 600
# define IMG_WID 900
# define IMG_HIGH 600
# define MS 3

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>
# include "libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <pthread.h>

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*gda;
	int					bpp;
	int					sl;
	int					endian;
}						t_mlx;

typedef	struct			s_cords
{
	int					hit;
	int					side;
	int					map_x;
	int					map_y;
	int					map_w;
	int					map_h;
	int					step_x;
	int					step_y;
	double				w_d;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				d_dist_x;
	double				d_dist_y;
	double				s_dist_x;
	double				s_dist_y;
	double				ray_pos_x;
	double				ray_pos_y;
	double				ray_dir_x;
	double				ray_dir_y;
	double				camera_x;
	double				o_dir_x;
	double				o_pl_x;
}						t_cords;

typedef struct			s_draw
{
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					color;
}						t_draw;

typedef struct			s_all
{
	t_draw				draw;
	t_cords				var;
	t_mlx				mlx;
	char				**map;
}						t_all;

void					ft_image(t_all *all);
void					say_error(int code);
void					var_define(t_all *all, int x);
void					step_define(t_all *all);
void					start_end_define(t_all *all);
void					raycast(t_all *all);
int						exit_wolf(t_all *all);
int						key_hook(int code, t_all *all);

#endif
