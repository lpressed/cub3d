NAME = cub3D

SRCS = srcs/cub3d.c srcs/cub_parse.c srcs/cub_parse_sc.c srcs/cub_parse_map.c \
		srcs/cub_exit.c srcs/cub_key.c srcs/cub_img.c srcs/cub_raycasting.c \
		srcs/cub_parse_map_sc.c srcs/cub_valid_map.c srcs/cub_paint.c \
		srcs/cub_sprite.c srcs/cub_shot.c \
		utils/ft_atoi.c utils/ft_isdigit.c utils/ft_strchr.c utils/ft_strjoin.c \
		utils/ft_strlcpy.c utils/ft_strlen.c utils/ft_strncmp.c utils/get_next_line.c \
		utils/ft_strlcat.c utils/ft_strdup.c

HEAD = /.

OBB = $(SRCS:%.c=%.o)
DEP = $(SRCS:%.c=%.d)

all: $(NAME)

$(NAME): $(OBB)
	cd minilibx-linux && make
	gcc -Wall -Wextra -o $(NAME) $(OBB) -L./minilibx-linux -lmlx -lXext -lX11 -lm
	

%.o: %.c
	gcc -c -Wall -Wextra -Werror -MD -I $(HEAD) -o $@ $<

include $(wildcard $(DEP))

clean:
	/bin/rm -rf $(OBB) $(DEP)

fclean: clean
	/bin/rm -rf $(NAME)
	cd minilibx-linux && make clean

re: fclean all