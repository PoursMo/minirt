CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iminilibx-linux -Iheaders -g # remove -g
LFLAGS = -Llibft -lft -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm
NAME = miniRT
SRCSDIR = srcs/
SRCS =	minirt.c \
parsing/parsing_utils.c \
parsing/parsing.c \
utils/color.c \
utils/scene.c \
utils/vectors.c \
debug.c \
# remove


OBJSDIR = objects
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