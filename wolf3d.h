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
# define WIN_WID 1200
# define WIN_HIGH 900
# define IMG_WID 1200
# define IMG_HIGH 900

# include <stdlib.h>
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
	struct s_cords		*next;
	double				x;
	double				y;
}						t_cords;

typedef struct			s_all
{
	t_cords				*map;
	t_mlx				mlx;
}						t_all;

#endif