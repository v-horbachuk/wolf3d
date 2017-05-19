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

void	say_error(int code)
{
	if (code == 1)
	{
		ft_putstr("usage:\n");
		ft_putstr("       There should be only one argument\n");
		ft_putstr("       Use one of the 'map' files as argument\n");
	}
	exit(0);
}

t_all	read_map(int fd, t_all *all)
{

}

int 	main(int ac, char **av)
{
	int 	fd;
	t_all	*all;

	if (ac == 2)
	{
		all = (t_all *) malloc(sizeof(t_all));
		all->map = (t_cords *) malloc(sizeof(t_cords));
		fd = open(av[1], O_RDONLY);
		if (fd < 0) {
			write(1, "File not valid\n", 15);
			exit(1);
		}
		all->map = read_map(fd, all);
		mlx_define(all);
		close(fd);
	}
	else
		say_error(1);
	return (0);
}
