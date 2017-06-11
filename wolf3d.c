/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:20:16 by vhorbach          #+#    #+#             */
/*   Updated: 2017/06/08 20:07:19 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_line(int x, int s, int e, t_all *all)
{
	int		a;
	int		red;
	int		green;
	int		blue;

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

void		wall_color_define(t_all *all)
{
	if (all->var.side == 0)
	{
		if (all->var.step_x == 1)
			all->draw.color = 0x0000ff;
		else
			all->draw.color = 0xff0000;
	}
	else
	{
		if (all->var.step_y == -1)
			all->draw.color = 0x00ff00;
		else
			all->draw.color = 0xffff00;
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
		wall_color_define(all);
		draw_line(x, all->draw.draw_start, all->draw.draw_end, all);
		all->draw.color = 0x220077;
		draw_line(x, 0, all->draw.draw_start, all);
		all->draw.color = 0x227700;
		draw_line(x, all->draw.draw_end, IMG_HIGH - 1, all);
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

int			exit_wolf(t_all *all)
{
	all = NULL;
	exit(0);
}
