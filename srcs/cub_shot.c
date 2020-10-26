/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <lpressed@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 23:39:55 by lpressed          #+#    #+#             */
/*   Updated: 2020/09/29 01:54:08 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void	bitmapheader(t_mlx *mlx, t_data *data, t_bitmapheader *bf)
{
	bf->size = mlx->map->width * mlx->map->heigth * data->bpp / 8 + 40 + 14;
	bf->reserved = 0;
	bf->offbits = 14 + 40;
}

static void	bitmapinfoheader(t_mlx *mlx, t_data *data, t_bitmapinfoheader *bi)
{
	bi->size = 40;
	bi->width = mlx->map->width;
	bi->height = -mlx->map->heigth;
	bi->planes = 1;
	bi->bitcount = data->bpp;
	bi->compression = 0;
	bi->sizeimage = mlx->map->width * mlx->map->heigth * data->bpp / 8;
	bi->xppm = 2835;
	bi->yppm = 2835;
	bi->clrused = 0;
	bi->clrimportant = 0;
}

int			screenshot(t_mlx *mlx, t_data *data)
{
	t_bitmapheader		bf;
	t_bitmapinfoheader	bi;
	int					fd;

	bitmapheader(mlx, data, &bf);
	bitmapinfoheader(mlx, data, &bi);
	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY |
					O_TRUNC, S_IRWXU)) == -1)
		return (-1);
	write(fd, "BM", 2);
	write(fd, &bf, 12);
	write(fd, &bi, 40);
	write(fd, data->addr, mlx->map->width * mlx->map->heigth * data->bpp / 8);
	close(fd);
	exit(EXIT_SUCCESS);
	return (1);
}
