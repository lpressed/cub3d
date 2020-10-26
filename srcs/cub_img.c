/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 19:16:12 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/30 02:26:13 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_addr(t_data *data)
{
	data->north.addr = mlx_get_data_addr(data->north.img, &(data->north.bpp),
			&(data->north.len), &(data->north.endian));
	data->south.addr = mlx_get_data_addr(data->south.img, &(data->south.bpp),
			&(data->south.len), &(data->south.endian));
	data->west.addr = mlx_get_data_addr(data->west.img, &(data->west.bpp),
			&(data->west.len), &(data->west.endian));
	data->east.addr = mlx_get_data_addr(data->east.img, &(data->east.bpp),
			&(data->east.len), &(data->east.endian));
	data->sprite.addr = mlx_get_data_addr(data->sprite.img, &(data->sprite.bpp),
			&(data->sprite.len), &(data->sprite.endian));
	return (1);
}

static int	destroy_img(t_mlx *mlx)
{
	if (mlx->data.north.img != NULL)
		mlx_destroy_image(mlx->ptr, mlx->data.north.img);
	if (mlx->data.south.img != NULL)
		mlx_destroy_image(mlx->ptr, mlx->data.south.img);
	if (mlx->data.west.img != NULL)
		mlx_destroy_image(mlx->ptr, mlx->data.west.img);
	if (mlx->data.east.img != NULL)
		mlx_destroy_image(mlx->ptr, mlx->data.east.img);
	if (mlx->data.sprite.img != NULL)
		mlx_destroy_image(mlx->ptr, mlx->data.sprite.img);
	return (-1);
}

int			load_textures(t_mlx *mlx, t_data *data)
{
	mlx->data.north.img = NULL;
	mlx->data.south.img = NULL;
	mlx->data.west.img = NULL;
	mlx->data.east.img = NULL;
	mlx->data.sprite.img = NULL;
	if ((data->north.img = mlx_xpm_file_to_image(mlx->ptr, mlx->map->no,
					&(data->north.w), &(data->north.h))) == NULL)
		return (destroy_img(mlx));
	if ((data->south.img = mlx_xpm_file_to_image(mlx->ptr, mlx->map->so,
					&(data->south.w), &(data->south.h))) == NULL)
		return (destroy_img(mlx));
	if ((data->west.img = mlx_xpm_file_to_image(mlx->ptr, mlx->map->we,
					&(data->west.w), &(data->west.h))) == NULL)
		return (destroy_img(mlx));
	if ((data->east.img = mlx_xpm_file_to_image(mlx->ptr, mlx->map->ea,
					&(data->east.w), &(data->east.h))) == NULL)
		return (destroy_img(mlx));
	if ((data->sprite.img = mlx_xpm_file_to_image(mlx->ptr, mlx->map->s,
					&(data->sprite.w), &(data->sprite.h))) == NULL)
		return (destroy_img(mlx));
	get_addr(data);
	return (1);
}

int			init_img(t_mlx *mlx)
{
	mlx->data.img = mlx_new_image(mlx->ptr, mlx->map->width, mlx->map->heigth);
	if (mlx->data.img == NULL)
		error_sc(mlx, 1);
	mlx->data.addr = mlx_get_data_addr(mlx->data.img, &(mlx->data.bpp),
			&(mlx->data.len), &(mlx->data.endian));
	cub_raycasting(mlx, &(mlx->data), mlx->pl);
	if (mlx->map->flag_shot == 1)
		screenshot(mlx, &(mlx->data));
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->data.img, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->data.img);
	return (1);
}

void		pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dest;

	dest = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dest = color;
}
