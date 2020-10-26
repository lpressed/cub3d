/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_paint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 23:48:26 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/28 23:40:15 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			paint_flour(t_mlx *mlx, t_data *data, int x, int end)
{
	int	n;

	n = mlx->map->heigth - 1;
	while (end != n)
	{
		pixel_put(data, x, end, create_trgb(1, mlx->map->f_red,
			mlx->map->f_green, mlx->map->f_blue));
		end++;
	}
	return (1);
}

int			paint_ceiling(t_mlx *mlx, t_data *data, int x, int begin)
{
	int	n;

	n = 0;
	while (n != begin)
	{
		pixel_put(data, x, n, create_trgb(1, mlx->map->c_red,
			mlx->map->c_green, mlx->map->c_blue));
		n++;
	}
	return (1);
}

static int	calc_texx(t_data *data, t_cam *cam, t_player *pl)
{
	double	wallx;
	int		texx;

	if (cam->side == 0 || cam->side == 1)
		wallx = pl->posy + cam->dist_wall * cam->ray_diry;
	else
		wallx = pl->posx + cam->dist_wall * cam->ray_dirx;
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)data->north.w);
	if (cam->side == 0 || cam->side == 3)
		texx = data->north.w - texx - 1;
	return (texx);
}

static int	get_tex_color(t_cam *cam, t_data *data, int texx, int texy)
{
	int color;

	if (cam->side == 0)
		color = *(int*)(data->north.addr + (texy * data->north.len +
					texx * (data->north.bpp / 8)));
	if (cam->side == 3)
		color = *(int*)(data->west.addr + (texy * data->west.len +
					texx * (data->west.bpp / 8)));
	if (cam->side == 2)
		color = *(int*)(data->east.addr + (texy * data->east.len +
					texx * (data->east.bpp / 8)));
	if (cam->side == 1)
		color = *(int*)(data->south.addr + (texy * data->south.len +
					texx * (data->south.bpp / 8)));
	return (color);
}

int			get_textures(t_mlx *mlx, t_data *data, t_cam *cam, t_player *pl)
{
	double	step;
	double	tex_pos;
	int		texx;
	int		texy;
	int		color;

	texx = calc_texx(data, cam, pl);
	step = 1.0 * data->north.w / cam->h;
	tex_pos = (cam->begin - mlx->map->heigth / 2 + cam->h / 2) * step;
	while (cam->begin != cam->end)
	{
		texy = (int)tex_pos & (data->north.h - 1);
		tex_pos += step;
		color = get_tex_color(cam, data, texx, texy);
		pixel_put(data, cam->x, cam->begin, color);
		cam->begin++;
	}
	return (1);
}
