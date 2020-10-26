/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:42:27 by lpressed          #+#    #+#             */
/*   Updated: 2020/10/01 01:24:24 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		init_map(t_map *map)
{
	map->width = 0;
	map->heigth = 0;
	map->f_red = 0;
	map->f_green = 0;
	map->f_blue = 0;
	map->c_red = 0;
	map->c_green = 0;
	map->c_blue = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->s = NULL;
	map->sum = 0;
	map->position = '0';
	map->n_map = 0;
	map->w_map = 0;
	map->start_pos_x = 0;
	map->start_pos_y = 0;
	map->map_form = NULL;
	map->map_buf = NULL;
	map->n_sprite = 0;
	map->flag_shot = 0;
}

static int		check_cub(char *src, int type)
{
	if (type == 0)
	{
		while (*src != '\0' && *src != '.')
			src++;
		if (*src == '.' && ft_strncmp(src + 1, "cub", 4) == 0)
			return (0);
	}
	if (type == 1)
		if (ft_strncmp(src, "--save", 7) == 0)
			return (0);
	return (1);
}

static void		init_player(t_player *pl, t_map *map)
{
	int k1;
	int k2;

	k1 = 0;
	k2 = 0;
	pl->posx = map->start_pos_x + 0.5;
	pl->posy = map->start_pos_y + 0.5;
	if (map->position == 'E')
		k2 = -1;
	if (map->position == 'W')
		k2 = 1;
	if (map->position == 'S')
		k1 = -1;
	if (map->position == 'N')
		k1 = 1;
	pl->dirx = -k1;
	pl->diry = k2;
	pl->planex = -0.88 * k2;
	pl->planey = -0.88 * k1;
	pl->speed = 0.1;
	pl->rotspeed = 0.05;
	pl->updx = 0;
	pl->updy = 0;
	map->x_max = map->width;
	map->y_max = map->heigth;
}

int				run_mlx(t_map *map)
{
	t_mlx		mlx;
	t_player	pl;
	int			x[map->n_sprite];
	int			y[map->n_sprite];

	mlx.map = map;
	map->x_sprite = x;
	map->y_sprite = y;
	get_xy_sprite(map);
	init_player(&pl, map);
	mlx.pl = pl;
	if ((mlx.ptr = mlx_init()) == NULL)
		return (-1);
	screen_size(&mlx, map);
	if (load_textures(&mlx, &mlx.data) == -1)
		error_sc(&mlx, 2);
	if (map->flag_shot != 1)
		mlx.win = mlx_new_window(mlx.ptr, map->width, map->heigth, "main_win");
	init_img(&mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_pressed, &mlx);
	mlx_hook(mlx.win, 3, 1L << 2, key_release, &mlx);
	mlx_hook(mlx.win, 17, 1L << 17, exit_prog, &mlx);
	mlx_loop(mlx.ptr);
	return (1);
}

int				main(int argc, char **argv)
{
	t_map	map;

	if (argc < 2 || argv[1] == NULL || check_cub(argv[1], 0))
		error(&map, 0);
	init_map(&map);
	if (argc > 2 && !check_cub(argv[2], 1))
		map.flag_shot = 1;
	if (cub_parse(&map, argv[1]) == -1 || cub_valid_map(&map) == -1)
		error(&map, 2);
	if (run_mlx(&map) == -1)
		error(&map, 1);
	return (0);
}
