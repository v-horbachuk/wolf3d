/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:46:13 by vhorbach          #+#    #+#             */
/*   Updated: 2017/05/19 15:46:16 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_hook(int code, t_all *all)
{
	if (code == 53)
		exit(0);
	if (code == 126)
	{
		if(all->map[(int)(all->var.pos_x + all->var.dir_x / MS)][(int)all->var.pos_y] == '0')
			all->var.pos_x += all->var.dir_x / MS;
		if(all->map[(int)all->var.pos_x][(int)(all->var.pos_y + all->var.dir_y / MS)] == '0')
			all->var.pos_y += all->var.dir_y / MS;
		ft_image(all);
	}
	if (code == 125)
	{
		if(all->map[(int)(all->var.pos_x - all->var.dir_x / MS)][(int)all->var.pos_y] == '0')
			all->var.pos_x -= all->var.dir_x / MS;
		if(all->map[(int)all->var.pos_x][(int)(all->var.pos_y - all->var.dir_y / MS)] == '0')
			all->var.pos_y -= all->var.dir_y / MS;
		ft_image(all);
	}
	if (code == 124)
	{
		double		rad;

		rad = M_PI * 2 / 180;
		all->var.o_dir_x = all->var.dir_x;
		all->var.dir_x = all->var.dir_x * cos(-rad) - all->var.dir_y * sin(-rad);
		all->var.dir_y = all->var.o_dir_x * sin(-rad) + all->var.dir_y * cos(-rad);
		all->var.o_pl_x = all->var.plane_x;
		all->var.plane_x = all->var.plane_x * cos(-rad) - all->var.plane_y * sin(-rad);
		all->var.plane_y= all->var.o_pl_x * sin(-rad) + all->var.plane_y * cos(-rad);
		ft_image(all);
	}
	if (code == 123)
	{
		double		rad;

		rad =  M_PI * 2 / 180;
		all->var.o_dir_x = all->var.dir_x;
		all->var.dir_x = all->var.dir_x * cos(rad) - all->var.dir_y * sin(rad);
		all->var.dir_y = all->var.o_dir_x * sin(rad) + all->var.dir_y * cos(rad);
		all->var.o_pl_x = all->var.plane_x;
		all->var.plane_x = all->var.plane_x * cos(rad) - all->var.plane_y * sin(rad);
		all->var.plane_y= all->var.o_pl_x * sin(rad) + all->var.plane_y * cos(rad);
		ft_image(all);
	}
	return (0);
}

int 		exit_wolf(t_all *all)
{
	all->draw.color = 0;
	exit(0);
}

void		mlx_define(t_all *all)
{
	all->mlx.mlx = mlx_init();
	all->mlx.win = mlx_new_window(all->mlx.mlx, WIN_WID, WIN_HIGH, "wolf3d");
	all->var.pos_x = 19;
	all->var.pos_y = 7;
	if (all->map[(int)all->var.pos_x][(int)all->var.pos_y] == '1')
		say_error(6);
	all->var.dir_x = -1.;
	all->var.dir_y = 0.;
	all->var.plane_x = 0.;
	all->var.plane_y = 0.66;
	ft_image(all);
	mlx_hook(all->mlx.win, 2, 3, key_hook, all);
	mlx_hook(all->mlx.win, 17, 1L << 17, exit_wolf, all);
	mlx_loop(all->mlx.mlx);
}

void	say_error(int code)
{
	if (code == 1)
	{
		ft_putstr("usage:\n");
		ft_putstr("       There should be only one argument\n");
		ft_putstr("       Use one of the 'map' files as argument\n");
	}
	else if (code == 2)
		ft_putstr("Cannot read the file");
	else if (code == 3)
		ft_putstr("File not valid");
	else if (code == 4)
		ft_putstr("Malloc error, bro!");
	else if (code == 5)
		ft_putstr("Map not valid");
	else if (code == 6)
		ft_putstr("Wrong player position");
	exit(0);
}

void 	map_size(t_all *all, char *line)
{
	int 	i;

	i = 0;
	if (line[i] < 48 || line [i] > 57)
		say_error(5);
	all->var.map_w = ft_atoi(line);
	while (line[i])
	{
		if ((line[i] < 48 || line [i] > 57))
			break ;
		i++;
	}
	line = ft_strsub(line, (unsigned int)i, 3);
	all->var.map_h = ft_atoi(line);
	if (all->var.map_w > 99 || all->var.map_w < 3)
		say_error(5);
	if (all->var.map_h > 99 || all->var.map_h < 3)
		say_error(5);
}

char	**read_map(int fd, t_all *all)
{
	char 	**map;
	char 	*line;
	int 	i;

	line = NULL;
	i = 0;
	get_next_line(fd, &line);
	map_size(all, line);
	free(line);
	map = (char **)malloc(sizeof(char *) * all->var.map_w + 1);
	if (!map)
		say_error(4);
	while (get_next_line(fd, &line))
	{
		map[i] = ft_strdup(line);
		i++;
	}
	free(line);
	all->map = map;
	return (all->map);
}

int 	main(int ac, char **av)
{
	int 	fd;
	t_all	*all;

	if (ac == 2)
	{
		all = (t_all *) malloc(sizeof(t_all));
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			say_error(3);
		read_map(fd, all);
		mlx_define(all);
		close(fd);
	}
	else
		say_error(1);
	return (0);
}
