/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 22:25:23 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/30 01:10:40 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_direction(t_mlx *mlx, t_player pl, t_cam *cam)
{
	cam->plane_cam = (2 * cam->x) / (double)mlx->map->width - 1;
	cam->ray_dirx = pl.dirx + pl.planex * cam->plane_cam;
	cam->ray_diry = pl.diry + pl.planey * cam->plane_cam;
	cam->delta_distx = sqrt(1.0 + (cam->ray_diry * cam->ray_diry) /
			(cam->ray_dirx * cam->ray_dirx));
	cam->delta_disty = sqrt(1.0 + (cam->ray_dirx * cam->ray_dirx) /
			(cam->ray_diry * cam->ray_diry));
	if (cam->ray_dirx < 0)
		cam->stepx = -1;
	else
		cam->stepx = 1;
	cam->side_distx = ((cam->cur_mapx - pl.posx) * cam->stepx +
			(0.5 + 0.5 * cam->stepx)) * cam->delta_distx;
	if (cam->ray_diry < 0)
		cam->stepy = -1;
	else
		cam->stepy = 1;
	cam->side_disty = ((cam->cur_mapy - pl.posy) * cam->stepy +
			(0.5 + 0.5 * cam->stepy)) * cam->delta_disty;
}

static void	calc_walldist(t_mlx *mlx, t_cam *cam)
{
	while (mlx->map->n_map >= cam->cur_mapy &&
			mlx->map->w_map[cam->cur_mapy] >= cam->cur_mapx &&
			mlx->map->map_form[cam->cur_mapy][cam->cur_mapx] != '1')
	{
		if (cam->side_distx < cam->side_disty)
		{
			cam->side_distx += cam->delta_distx;
			cam->cur_mapx += cam->stepx;
			if (cam->stepx < 0)
				cam->side = 0;
			else
				cam->side = 1;
		}
		else
		{
			cam->side_disty += cam->delta_disty;
			cam->cur_mapy += cam->stepy;
			if (cam->stepy < 0)
				cam->side = 2;
			else
				cam->side = 3;
		}
	}
}

static void	put_in_data(t_mlx *mlx, t_data *data, t_cam *cam, t_player *pl)
{
	if (cam->side == 0 || cam->side == 1)
		cam->dist_wall = (cam->cur_mapx - pl->posx + (1 - cam->stepx)
				/ 2.0) / cam->ray_dirx;
	else
		cam->dist_wall = (cam->cur_mapy - pl->posy + (1 - cam->stepy)
				/ 2.0) / cam->ray_diry;
	cam->h = (int)(mlx->map->width / 2 / cam->dist_wall);
	cam->begin = -cam->h / 2 + mlx->map->heigth / 2;
	if (cam->begin < 0)
		cam->begin = 0;
	cam->end = cam->h / 2 + mlx->map->heigth / 2;
	if (cam->end >= mlx->map->heigth)
		cam->end = mlx->map->heigth - 1;
	paint_ceiling(mlx, data, cam->x, cam->begin);
	paint_flour(mlx, data, cam->x, cam->end);
	get_textures(mlx, data, cam, pl);
}

int			cub_raycasting(t_mlx *mlx, t_data *data, t_player pl)
{
	t_cam		cam;
	t_sprite	sp;
	double		distwall[mlx->map->width];

	cam.x = 0;
	while (cam.x < mlx->map->width)
	{
		cam.cur_mapx = (int)pl.posx;
		cam.cur_mapy = (int)pl.posy;
		init_direction(mlx, pl, &cam);
		calc_walldist(mlx, &cam);
		put_in_data(mlx, data, &cam, &pl);
		distwall[cam.x] = cam.dist_wall;
		cam.x++;
	}
	sp.dist_wall = distwall;
	cub_sprite(mlx->map, &pl, &sp, data);
	return (1);
}
