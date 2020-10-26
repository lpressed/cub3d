/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 19:09:23 by lpressed          #+#    #+#             */
/*   Updated: 2020/10/01 01:14:44 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	print_error(char *str)
{
	write(1, str, ft_strlen(str));
}

void		error(t_map *map, int type)
{
	if (type == 0)
		print_error("ERROR: invalid arguments\n");
	else if (type == 1)
	{
		free_map_form(map, map->n_map);
		free_map_filename(map);
		print_error("ERROR: mlx not init\n");
	}
	else if (type == 2)
		print_error("ERROR: invalid config file\n");
	else
		write(1, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

void		error_sc(t_mlx *mlx, int type)
{
	if (type == 1)
	{
		mlx_destroy_image(mlx->ptr, mlx->data.north.img);
		mlx_destroy_image(mlx->ptr, mlx->data.south.img);
		mlx_destroy_image(mlx->ptr, mlx->data.west.img);
		mlx_destroy_image(mlx->ptr, mlx->data.east.img);
		mlx_destroy_image(mlx->ptr, mlx->data.sprite.img);
		free_map_form(mlx->map, mlx->map->n_map);
		free_map_filename(mlx->map);
		print_error("ERROR: main image not created\n");
	}
	else if (type == 2)
	{
		free_map_form(mlx->map, mlx->map->n_map);
		free_map_filename(mlx->map);
		print_error("ERROR: invalid textures\n");
	}
	else
		write(1, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

int			exit_prog(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->data.north.img);
	mlx_destroy_image(mlx->ptr, mlx->data.south.img);
	mlx_destroy_image(mlx->ptr, mlx->data.west.img);
	mlx_destroy_image(mlx->ptr, mlx->data.east.img);
	mlx_destroy_image(mlx->ptr, mlx->data.sprite.img);
	free_map_form(mlx->map, mlx->map->n_map);
	free_map_filename(mlx->map);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(EXIT_SUCCESS);
}
