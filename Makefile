CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iminilibx-linux -Iheaders
LFLAGS = -Llibft -lft -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm
NAME = fdf
SRCSDIR = srcs/
SRCS =	minirt.c \

OBJSDIR = objects
OBJS = $(SRCS:%.c=$(OBJSDIR)/%.o)
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) -o $@ $(LFLAG)

$(MLX):
	cd minilibx-linux && ./configure && cd ..

$(LIBFT):
	make -C libft

$(OBJSDIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all