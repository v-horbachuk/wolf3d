/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:46:13 by vhorbach          #+#    #+#             */
/*   Updated: 2017/06/08 20:02:44 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	mlx_define(t_all *all)
{
	all->mlx.mlx = mlx_init();
	all->mlx.win = mlx_new_window(all->mlx.mlx, WIN_WID, WIN_HIGH, "wolf3d");
	all->var.pos_x = 19;
	all->var.pos_y = 2;
	if (all->map[(int)all->var.pos_x][(int)all->var.pos_y] == '1')
		say_error(6);
	all->var.dir_x = -0.999;
	all->var.dir_y = 0.;
	all->var.plane_x = 0;
	all->var.plane_y = 0.6;
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
		ft_putstr("       There should be no argument\n");
		ft_putstr("       Run only 'wolf3d' executable\n");
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

void	map_size(t_all *all, char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	all->var.map_w = ft_atoi(line);
	while (*line && !(ft_isspace(*line)))
		line++;
	all->var.map_h = ft_atoi(line);
	if (all->var.map_w > 99 || all->var.map_w < 3)
		say_error(5);
	if (all->var.map_h > 99 || all->var.map_h < 3)
		say_error(5);
}

void	read_map(int fd, t_all *all)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	get_next_line(fd, &line);
	map_size(all, line);
	free(line);
	all->map = (char **)malloc(sizeof(char *) * all->var.map_h + 1);
	if (!all->map)
		say_error(4);
	all->map[all->var.map_h] = 0;
	while (i < all->var.map_h && get_next_line(fd, &all->map[i]) > 0)
		i++;
	close(fd);
}

int		main(int ac, char **av)
{
	int		fd;
	t_all	all;

	if (ac >= 2 || !(av[0]))
		say_error(1);
	fd = open(MAP, O_RDONLY);
	if (fd < 0)
		say_error(3);
	read_map(fd, &all);
	mlx_define(&all);
	return (0);
}
