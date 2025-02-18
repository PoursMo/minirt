#include "minirt.h"

void print_scene(t_scene *scene); // debug.c

int main(int argc, char **argv)
{
	// check file is .rt
	if (parse_file(argv[argc - 1]) == -1)
		return (1);
	print_scene(get_scene());
}




// void fill_img(void *img)
// {
// 	int bpp, sl, endian;
// 	char *data = mlx_get_data_addr(img, &bpp, &sl, &endian);
// 	printf("OK (bpp: %d, sizeline: %d endian: %d type: %d)\n",bpp,sl,endian,((t_img *)img)->type);  
// 	for (int y = 0; y < 10; y++)
// 	{
// 		for (int x = 0; x < 10; x++)
// 		{
// 			int pixel = (y * sl) + (x * (bpp / 8));
// 			data[pixel + 0] = 0x00; // Blue
// 			data[pixel + 1] = 0x00; // Green
// 			data[pixel + 2] = 0xFF; // Red
// 			data[pixel + 3] = 0x00; // Alpha
// 		}
// 	}
// }

// int main()
// {
// 	int local_endian;
// 	int a = 0x11223344;
// 	if (((unsigned char *)&a)[0] == 0x11)
// 		local_endian = 1;
// 	else
// 		local_endian = 0;
// 	printf(" => Local Endian : %d\n",local_endian);

// 	void *mlx;
// 	void *win;
// 	void *img;
// 	if (!(mlx = mlx_init()))
//     {
//     	printf(" !! KO !!\n");
//     	exit(1);
//     }
// 	if (!(win = mlx_new_window(mlx, 250, 250, "Title1")))
//     {
//     	printf(" !! KO !!\n");
//     	exit(1);
//     }
// 	if (!(img = mlx_new_image(mlx, 10, 10)))
//     {
//     	printf(" !! KO !!\n");
//     	exit(1);
//     }
// 	fill_img(img);
// 	mlx_put_image_to_window(mlx, win, img, 20, 20);
// 	mlx_loop(mlx);
// }