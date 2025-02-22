#include "minirt.h"

// ** debug.c **
void print_scene(t_scene *scene);
void fill_img(void *img);
// *************

typedef struct test
{
	void *mlx;
	void *win;
	void *img;
} test;

int mrt_terminate(void *ptr)
{
	test *t;

	t = (test *)ptr;
	free_scene();
	mlx_destroy_image(t->mlx, t->img);
	mlx_destroy_window(t->mlx, t->win);
	mlx_destroy_display(t->mlx);
	free(t->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int handle_key(int keycode, void *ptr)
{
	if (keycode == ESC_KEY)
		mrt_terminate(ptr);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), EXIT_FAILURE);
	if (parse_file(argv[argc - 1]) == -1)
		return (1);
	print_scene(get_scene()); // debug

	// get endian
	int local_endian;
	int a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	printf(" => Local Endian : %d\n",local_endian);

	// initialize mlx stuff
	test t;
	if (!(t.mlx = mlx_init()))
    {
    	printf(" !! KO !!\n");
    	exit(1);
    }
	if (!(t.win = mlx_new_window(t.mlx, WIDTH, HEIGHT, "miniRT")))
    {
    	printf(" !! KO !!\n");
    	exit(1);
    }
	if (!(t.img = mlx_new_image(t.mlx, 100, 100)))
    {
    	printf(" !! KO !!\n");
    	exit(1);
    }
	fill_img(t.img);
	mlx_put_image_to_window(t.mlx, t.win, t.img, WIDTH / 2, HEIGHT / 2);
	mlx_hook(t.win, DestroyNotify, 0, mrt_terminate, &t);
	mlx_key_hook(t.win, handle_key, &t);
	mlx_loop(t.mlx);
}