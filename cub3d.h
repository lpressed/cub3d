/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpressed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:43:05 by lpressed          #+#    #+#             */
/*   Updated: 2020/10/01 01:25:52 by lpressed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 100
# define KEY_S 115
# define KEY_D 97
# define KEY_LEFT_ARROW 65363
# define KEY_RIGHT_ARROW 65361

# define BUFFER_SIZE 64

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "minilibx-linux/mlx.h"
# include <math.h>

typedef struct			s_map
{
	int					width;
	int					heigth;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*s;
	int					f_red;
	int					f_green;
	int					f_blue;
	int					c_red;
	int					c_green;
	int					c_blue;
	int					sum;
	char				*map_buf;
	char				**map_form;
	char				position;
	int					n_map;
	int					*w_map;
	int					start_pos_x;
	int					start_pos_y;
	int					n_sprite;
	int					*x_sprite;
	int					*y_sprite;
	int					flag_shot;
	int					x_max;
	int					y_max;
}						t_map;

typedef struct			s_tex
{
	void				*img;
	char				*addr;
	int					bpp;
	int					len;
	int					endian;
	int					w;
	int					h;
}						t_tex;

typedef struct			s_data
{
	void				*img;
	t_tex				east;
	t_tex				north;
	t_tex				west;
	t_tex				south;
	t_tex				sprite;
	char				*addr;
	int					bpp;
	int					len;
	int					endian;
}						t_data;

typedef struct			s_player
{
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;
	double				speed;
	double				rotspeed;
	double				updx;
	double				updy;
}						t_player;

typedef struct			s_cam
{
	double				plane_cam;
	double				side_distx;
	double				side_disty;
	double				delta_distx;
	double				delta_disty;
	double				dist_wall;
	double				ray_dirx;
	double				ray_diry;
	int					cur_mapx;
	int					cur_mapy;
	int					stepx;
	int					stepy;
	int					side;
	int					x;
	int					h;
	int					begin;
	int					end;
}						t_cam;

typedef struct			s_sprite
{
	double				*dist_wall;
	double				*dist_sprite;
	double				revx;
	double				revy;
	int					*order_sprite;
	int					spritehw;
	int					beginx;
	int					beginy;
	int					endx;
	int					endy;
	int					i;
}						t_sprite;

typedef struct			s_bitmapheader
{
	unsigned int		size;
	unsigned int		reserved;
	unsigned int		offbits;
}						t_bitmapheader;

typedef struct			s_bitmapinfoheader
{
	unsigned int		size;
	unsigned int		width;
	unsigned int		height;
	unsigned short int	planes;
	unsigned short int	bitcount;
	unsigned int		compression;
	unsigned int		sizeimage;
	unsigned int		xppm;
	unsigned int		yppm;
	unsigned int		clrused;
	unsigned int		clrimportant;
}						t_bitmapinfoheader;

typedef struct			s_mlx
{
	t_map				*map;
	t_player			pl;
	t_data				data;
	void				*ptr;
	void				*win;
}						t_mlx;

int						main(int argc, char **argv);
int						cub_parse(t_map *map, char *file);
void					error(t_map *map, int type);
int						is_rgb(char *line, int *red, int *green, int *blue);
int						is_filename(char *line, char **filename);
int						map_parse(t_map *map);
int						run_mlx(t_map *map);
int						key_pressed(int key, t_mlx *mlx);
int						key_release(int key, t_mlx *mlx);
int						exit_prog(t_mlx *mlx);
int						init_img(t_mlx *mlx);
void					pixel_put(t_data *data, int x, int y,
		unsigned int color);
int						cub_raycasting(t_mlx *mlx, t_data *data, t_player pl);
int						join_line(t_map *map, char *line);
int						check_line(t_map *map, char *line);
int						check_spaces(char *line);
int						free_map_form(t_map *map, int n);
int						free_map_filename(t_map *map);
int						calc_map_w(t_map *map);
int						cub_valid_map(t_map *map);
int						free_map_buf(t_map *map);
int						create_trgb(int t, int r, int g, int b);
int						paint_flour(t_mlx *mlx, t_data *data, int x, int end);
int						paint_ceiling(t_mlx *mlx, t_data *data, int x,
		int begin);
int						cub_sprite(t_map *map, t_player *pl, t_sprite *sp,
		t_data *data);
int						get_textures(t_mlx *mlx, t_data *data, t_cam *cam,
		t_player *pl);
int						get_xy_sprite(t_map *map);
int						screenshot(t_mlx *mlx, t_data *data);
int						load_textures(t_mlx *mlx, t_data *data);
int						ft_atoi(const char *nptr);
int						ft_isdigit(int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strjoin(char *s1, char const *s2);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						get_next_line(int fd, char **line);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strdup(const char *s);
void					error_sc(t_mlx *mlx, int type);
void					screen_size(t_mlx *mlx, t_map *map);

#endif
