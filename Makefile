CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iminilibx-linux -Iminirt/headers -g # remove -g
LFLAGS = -Llibft -lft -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm
NAME = miniRT
SRCSDIR = srcs/
SRCS =	minirt/main.c \
minirt/parsing/parsing.c \
minirt/parsing/parsing_utils.c \
minirt/parsing/parsing_utils2.c \
minirt/parsing/parsing_shape_getters.c \
minirt/parsing/parsing_type_getters.c \
minirt/parsing/parsing_type_getters2.c \
minirt/parsing/parsing_unique_getters.c \
minirt/utils/color.c \
minirt/utils/utils.c \
minirt/utils/utils2.c \
minirt/utils/termination.c \
minirt/utils/vectors.c \
minirt/utils/vectors2.c \
minirt/algo/rendering.c \
minirt/algo/tracing.c \
minirt/algo/intersections.c \
minirt/algo/uvs.c \
minirt/algo/phong.c \
minirt/algo/bump.c \
minirt/algo/lighting.c \
minirt/algo/normal.c \
minirt/algo/cone.c \
minirt/algo/cylinder.c \
minirt/debug.c \
# remove


OBJSDIR = minirt/objects
OBJS = $(SRCS:%.c=$(OBJSDIR)/%.o)
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LFLAGS)

$(MLX):
	cd minilibx-linux && ./configure && cd ..

$(LIBFT):
	make -C libft

$(OBJSDIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	cd minilibx-linux && ./configure clean && cd ..

re: fclean all