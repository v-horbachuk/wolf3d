/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 19:32:12 by vhorbach          #+#    #+#             */
/*   Updated: 2017/06/08 19:57:03 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	rotation_right(t_all *all)
{
	double rad;

	rad = M_PI * 2 / 180;
	all->var.o_dir_x = all->var.dir_x;
	all->var.dir_x = all->var.dir_x * cos(-rad)
		- all->var.dir_y * sin(-rad);
	all->var.dir_y = all->var.o_dir_x * sin(-rad)
		+ all->var.dir_y * cos(-rad);
	all->var.o_pl_x = all->var.plane_x;
	all->var.plane_x = all->var.plane_x * cos(-rad)
		- all->var.plane_y * sin(-rad);
	all->var.plane_y = all->var.o_pl_x * sin(-rad)
		+ all->var.plane_y * cos(-rad);
}

void	rotation_left(t_all *all)
{
	double		rad;

	rad = M_PI * 2 / 180;
	all->var.o_dir_x = all->var.dir_x;
	all->var.dir_x = all->var.dir_x * cos(rad)
		- all->var.dir_y * sin(rad);
	all->var.dir_y = all->var.o_dir_x * sin(rad)
		+ all->var.dir_y * cos(rad);
	all->var.o_pl_x = all->var.plane_x;
	all->var.plane_x = all->var.plane_x * cos(rad)
		- all->var.plane_y * sin(rad);
	all->var.plane_y = all->var.o_pl_x * sin(rad)
		+ all->var.plane_y * cos(rad);
}

void	move(t_all *all, int code)
{
	if (code == 1)
	{
		if (all->map[(int)(all->var.pos_x + all->var.dir_x
					/ MS)][(int)all->var.pos_y] == '0')
			all->var.pos_x += all->var.dir_x / MS;
		if (all->map[(int)all->var.pos_x][(int)(all->var.pos_y
												+ all->var.dir_y / MS)] == '0')
			all->var.pos_y += all->var.dir_y / MS;
	}
	else if (code == 0)
	{
		if (all->map[(int)(all->var.pos_x - all->var.dir_x
					/ MS)][(int)all->var.pos_y] == '0')
			all->var.pos_x -= all->var.dir_x / MS;
		if (all->map[(int)all->var.pos_x][(int)(all->var.pos_y
												- all->var.dir_y / MS)] == '0')
			all->var.pos_y -= all->var.dir_y / MS;
	}
}

int		key_hook(int code, t_all *all)
{
	if (code == 53)
		exit(0);
	if (code == 126)
		move(all, 1);
	if (code == 125)
		move(all, 0);
	if (code == 124)
		rotation_right(all);
	if (code == 123)
		rotation_left(all);
	ft_image(all);
	return (0);
}
