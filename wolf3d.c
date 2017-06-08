/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:20:16 by vhorbach          #+#    #+#             */
/*   Updated: 2017/05/24 17:20:19 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ver_line(int x, int s, int e, t_all *all)
{
	int		a;
	int		red;
	int		green;
	int 	blue;

	blue = all->draw.color % 256;
	green = (all->draw.color >> 8) % 256;
	red = all->draw.color >> 16;
	if (x < 0 || x >= WIN_WID || s < 0 || s >= WIN_HIGH)
		return ;
	while (s <= e)
	{
		a = (4 * (s * IMG_WID + x));
		all->mlx.gda[a] = (char)blue;
		all->mlx.gda[a + 1] = (char)green;
		all->mlx.gda[a + 2] = (char)red;
		s++;
	}
}

void		var_define(t_all *all, int x)
{
	all->var.camera_x = 2 * x / (double)IMG_WID - 1;
	all->var.ray_pos_x = all->var.pos_x;
	all->var.ray_pos_y = all->var.pos_y;
	all->var.ray_dir_x = all->var.dir_x + all->var.plane_x * all->var.camera_x;
	all->var.ray_dir_y = all->var.dir_y + all->var.plane_y * all->var.camera_x;
	all->var.map_x = (int)all->var.ray_pos_x;
	all->var.map_y = (int)all->var.ray_pos_y;
	all->var.d_dist_x = sqrt(1 + (all->var.ray_dir_y * all->var.ray_dir_y) /
								 (all->var.ray_dir_x * all->var.ray_dir_x));
	all->var.d_dist_y = sqrt(1 + (all->var.ray_dir_x * all->var.ray_dir_x) /
								 (all->var.ray_dir_y * all->var.ray_dir_y));
}

void		step_define(t_all *all)
{
	if (all->var.ray_dir_x < 0)
	{
		all->var.step_x = -1;
		all->var.s_dist_x = (all->var.ray_pos_x - all->var.map_x) * all->var.d_dist_x;
	}
	else
	{
		all->var.step_x = 1;
		all->var.s_dist_x = (all->var.map_x + 1.0 - all->var.ray_pos_x) * all->var.d_dist_x;
	}
	if (all->var.ray_dir_y < 0)
	{
		all->var.step_y = -1;
		all->var.s_dist_y = (all->var.ray_pos_y - all->var.map_y) * all->var.d_dist_y;
	}
	else
	{
		all->var.step_y = 1;
		all->var.s_dist_y = (all->var.map_y + 1.0 - all->var.ray_pos_y) * all->var.d_dist_y;
	}
}

void		start_end_define(t_all *all)
{
	if (all->var.side == 0)
		all->var.w_d = (all->var.map_x - all->var.ray_pos_x +
						(1 - all->var.step_x) / 2) / all->var.ray_dir_x;
	else
		all->var.w_d = (all->var.map_y - all->var.ray_pos_y +
						(1 - all->var.step_y) / 2) / all->var.ray_dir_y;
	all->draw.line_height = (int)(IMG_HIGH / all->var.w_d);
	all->draw.draw_start = -all->draw.line_height / 2 + IMG_HIGH / 2;
	if (all->draw.draw_start < 0)
		all->draw.draw_start = 0;
	all->draw.draw_end = all->draw.line_height / 2 + IMG_HIGH / 2;
	if (all->draw.draw_end >= IMG_HIGH)
		all->draw.draw_end = IMG_HIGH - 1;
}

void		raycast(t_all *all)
{
	all->var.hit = 0;
	while (all->var.hit == 0)
	{
		if (all->var.s_dist_x < all->var.s_dist_y)
		{
			all->var.s_dist_x += all->var.d_dist_x;
			all->var.map_x += all->var.step_x;
			all->var.side = 0;
		}
		else
		{
			all->var.s_dist_y += all->var.d_dist_y;
			all->var.map_y += all->var.step_y;
			all->var.side = 1;
		}
		if (all->var.map_x >= 0 && all->var.map_x <= all->var.map_h && all->var.map_y >= 0 && all->var.map_y <= all->var.map_w)
		{
			if(all->map[all->var.map_x][all->var.map_y] > '0')
				all->var.hit = 1;
		}
	}
}

void		draw(t_all *all)
{
	int		x;

	x = -1;
	while (++x < IMG_WID)
	{
		var_define(all, x);
		step_define(all);
		raycast(all);
		start_end_define(all);
		if (all->map[all->var.map_x][all->var.map_y] > '1')
		{
			if (all->var.side == 0)
				all->draw.color = 0x009900;
			else
				all->draw.color = 0x00ff00;
		}
		else
			all->draw.color = 0x0000ff;
		ver_line(x, all->draw.draw_start, all->draw.draw_end, all);
	}
}

void		ft_image(t_all *all)
{
	all->mlx.img = mlx_new_image(all->mlx.mlx, IMG_WID, IMG_HIGH);
	all->mlx.gda = mlx_get_data_addr(all->mlx.img, &all->mlx.bpp,
									 &all->mlx.sl, &all->mlx.endian);
	draw(all);
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->mlx.img, 0, 0);
	mlx_string_put(all->mlx.mlx, all->mlx.win, 20, 20, 0x00ff00, "USAGE:");
	mlx_string_put(all->mlx.mlx, all->mlx.win, 20, 75,
				   0x00ff00, "Move: arrows");
	mlx_destroy_image(all->mlx.mlx, all->mlx.img);
}