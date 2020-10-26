/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 19:05:01 by lpressed          #+#    #+#             */
/*   Updated: 2020/10/01 01:27:11 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_map_wall(t_mlx *mlx)
{
	double x;
	double y;
	double xs;
	double ys;

	x = mlx->pl.posx + mlx->pl.updx * (1 + mlx->pl.speed * 0.1);
	y = mlx->pl.posy + mlx->pl.updy * (1 + mlx->pl.speed * 0.1);
	xs = mlx->pl.posx + mlx->pl.updx * 5;
	ys = mlx->pl.posy + mlx->pl.updy * 5;
	if (mlx->map->map_form[(int)y][(int)x] == '1')
		return (-1);
	if (mlx->map->map_form[(int)ys][(int)xs] == 's')
		return (-1);
	mlx->pl.posx += mlx->pl.updx;
	mlx->pl.posy += mlx->pl.updy;
	mlx->pl.updx = 0;
	mlx->pl.updy = 0;
	return (1);
}

static void	cam_rotation(t_mlx *mlx, int key)
{
	double	tmp;
	int		k;

	if (key == KEY_LEFT_ARROW)
		k = 1;
	else if (key == KEY_RIGHT_ARROW)
		k = -1;
	else
		k = 0;
	if (k != 0)
	{
		tmp = mlx->pl.dirx;
		mlx->pl.dirx = mlx->pl.dirx * cos(k * mlx->pl.rotspeed) -
			mlx->pl.diry * sin(k * mlx->pl.rotspeed);
		mlx->pl.diry = tmp * sin(k * mlx->pl.rotspeed) + mlx->pl.diry *
			cos(k * mlx->pl.rotspeed);
		tmp = mlx->pl.planex;
		mlx->pl.planex = mlx->pl.planex * cos(k * mlx->pl.rotspeed) -
			mlx->pl.planey * sin(k * mlx->pl.rotspeed);
		mlx->pl.planey = tmp * sin(k * mlx->pl.rotspeed) +
			mlx->pl.planey * cos(k * mlx->pl.rotspeed);
	}
}

int			key_pressed(int key, t_mlx *mlx)
{
	if (key == KEY_W)
	{
		mlx->pl.updx = mlx->pl.dirx * mlx->pl.speed;
		mlx->pl.updy = mlx->pl.diry * mlx->pl.speed;
	}
	if (key == KEY_S)
	{
		mlx->pl.updx = -mlx->pl.dirx * mlx->pl.speed;
		mlx->pl.updy = -mlx->pl.diry * mlx->pl.speed;
	}
	if (key == KEY_A)
	{
		mlx->pl.updx = -mlx->pl.diry * mlx->pl.speed;
		mlx->pl.updy = mlx->pl.dirx * mlx->pl.speed;
	}
	if (key == KEY_D)
	{
		mlx->pl.updx = mlx->pl.diry * mlx->pl.speed;
		mlx->pl.updy = -mlx->pl.dirx * mlx->pl.speed;
	}
	cam_rotation(mlx, key);
	if (check_map_wall(mlx))
		init_img(mlx);
	return (1);
}

int			key_release(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		exit_prog(mlx);
	return (1);
}

void		screen_size(t_mlx *mlx, t_map *map)
{
	mlx_get_screen_size(mlx->ptr, &map->x_max, &map->y_max);
	if (map->x_max < map->width)
		map->width = map->x_max;
	if (map->y_max < map->heigth)
		map->heigth = map->y_max;
}
