/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:18:11 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/30 01:04:37 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		sort_sprite(t_map *map, t_sprite *sp, t_player *pl)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < map->n_sprite)
	{
		sp->order_sprite[i] = i;
		sp->dist_sprite[i] = sqrt((pl->posx - (map->x_sprite[i] + 0.5)) *
			(pl->posx - (map->x_sprite[i] + 0.5)) + (pl->posy -
			(map->y_sprite[i] + 0.5)) * (pl->posy - (map->y_sprite[i] + 0.5)));
		i++;
	}
	i = 0;
	while (i < map->n_sprite - 1)
	{
		if (sp->dist_sprite[sp->order_sprite[i]] <
				sp->dist_sprite[sp->order_sprite[i + 1]])
		{
			tmp = sp->order_sprite[i];
			sp->order_sprite[i] = sp->order_sprite[i + 1];
			sp->order_sprite[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

static void		sprite_size(t_map *map, t_sprite *sp, t_player *pl)
{
	double	spx;
	double	spy;

	spx = map->x_sprite[sp->order_sprite[sp->i]] + 0.5 - pl->posx;
	spy = map->y_sprite[sp->order_sprite[sp->i]] + 0.5 - pl->posy;
	sp->revx = (pl->diry * spx - pl->dirx * spy) / (pl->planex *
			pl->diry - pl->dirx * pl->planey);
	sp->revy = (-pl->planey * spx + pl->planex * spy) / (pl->planex *
			pl->diry - pl->dirx * pl->planey);
	sp->spritehw = abs((int)(map->width / 2 / sp->revy));
	sp->beginx = -sp->spritehw / 2 + (int)(map->width / 2) *
		(1 + sp->revx / sp->revy);
	if (sp->beginx < 0)
		sp->beginx = 0;
	sp->endx = sp->spritehw / 2 + (int)(map->width / 2) *
		(1 + sp->revx / sp->revy);
	if (sp->endx >= map->width)
		sp->endx = map->width - 1;
	sp->beginy = -sp->spritehw / 2 + map->heigth / 2;
	if (sp->beginy < 0)
		sp->beginy = 0;
	sp->endy = sp->spritehw / 2 + map->heigth / 2;
	if (sp->endy >= map->heigth)
		sp->endy = map->heigth - 1;
}

static double	get_texx(t_map *map, t_sprite *sp, t_data *data)
{
	double texx;

	if (sp->spritehw / 2 > (int)(map->width / 2) *
			(1 + sp->revx / sp->revy))
	{
		texx = (double)data->sprite.w / sp->spritehw * (sp->spritehw -
				(sp->endx - sp->beginx));
	}
	else if (sp->spritehw / 2 == (int)(map->width / 2) *
			(1 + sp->revx / sp->revy))
	{
		texx = data->sprite.w / 2;
	}
	else
		texx = 0;
	return (texx);
}

static void		paint_sprite(t_map *map, t_sprite *sp, t_data *data)
{
	double	texx;
	double	texy;
	int		tmp;
	int		color;

	texx = get_texx(map, sp, data);
	tmp = sp->beginy;
	while (sp->beginx < sp->endx)
	{
		texy = 0;
		sp->beginy = tmp;
		if (sp->revy > 0 && sp->revy < sp->dist_wall[sp->beginx])
			while (sp->beginy < sp->endy)
			{
				texy += (double)data->sprite.h / sp->spritehw;
				color = *(int*)(data->sprite.addr + ((int)texy *
					data->sprite.len + (int)texx * (data->sprite.bpp / 8)));
				if (color != 0)
					pixel_put(data, sp->beginx, sp->beginy, color);
				sp->beginy++;
			}
		sp->beginx++;
		texx += (double)data->sprite.w / sp->spritehw;
	}
}

int				cub_sprite(t_map *map, t_player *pl, t_sprite *sp, t_data *data)
{
	double	dist_sprite[map->n_sprite];
	int		order_sprite[map->n_sprite];
	int		i;

	sp->dist_sprite = dist_sprite;
	sp->order_sprite = order_sprite;
	sort_sprite(map, sp, pl);
	i = 0;
	while (i < map->n_sprite)
	{
		sp->i = i;
		sprite_size(map, sp, pl);
		paint_sprite(map, sp, data);
		i++;
	}
	return (1);
}
