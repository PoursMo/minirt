#include "minirt.h"

static void print_vector3(t_vector3 v)
{
    printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

static void print_color(t_color c)
{
    printf("red: %u, green: %u, blue: %u\n", c.red, c.green, c.blue);
}

void print_scene(t_scene *scene)
{
	// **********************************************************************
    printf("Ambiant Light:\n");
    if (scene->ambiant_light)
    {
        printf("  Ratio: %f\n", scene->ambiant_light->ratio);
        printf("  Color: ");
        print_color(scene->ambiant_light->color);
    }
    else
        printf("  None\n");
	// **********************************************************************
    printf("Camera:\n");
    if (scene->camera)
    {
        printf("  Position: ");
        print_vector3(scene->camera->position);
        printf("  Direction: ");
        print_vector3(scene->camera->direction);
        printf("  FOV: %d\n", scene->camera->fov);
    }
    else
        printf("  None\n");
	// **********************************************************************
    printf("Light:\n");
    if (scene->light)
    {
        printf("  Position: ");
        print_vector3(scene->light->position);
        printf("  Brightness: %f\n", scene->light->brightness);
        printf("  Color: ");
        print_color(scene->light->color);
    }
    else
        printf("  None\n");
	// **********************************************************************
    printf("Spheres:\n");
    if (scene->spheres)
    {
        t_list *current = scene->spheres;
        while (current)
        {
            t_sphere *sphere = (t_sphere *)current->content;
            printf("  Sphere:\n");
    		printf("    Position: ");
    		print_vector3(sphere->position);
    		printf("    Diameter: %f\n", sphere->diameter);
    		printf("    Color: ");
    		print_color(sphere->color);
            current = current->next;
        }
    }
    else
        printf("  None\n");
	// **********************************************************************
    printf("Planes:\n");
    if (scene->planes)
    {
        t_list *current = scene->planes;
        while (current)
        {
            t_plane *plane = (t_plane *)current->content;
            printf("  Plane:\n");
    		printf("    Position: ");
    		print_vector3(plane->position);
    		printf("    Normal: ");
    		print_vector3(plane->normal);
    		printf("    Color: ");
    		print_color(plane->color);
            current = current->next;
        }
    }
    else
        printf("  None\n");
	// **********************************************************************
    printf("Cylinders:\n");
    if (scene->cylinders)
    {
        t_list *current = scene->cylinders;
        while (current)
        {
            t_cylinder *cylinder = (t_cylinder *)current->content;
            printf("  Cylinder:\n");
    		printf("    Position: ");
    		print_vector3(cylinder->position);
    		printf("    Axis: ");
    		print_vector3(cylinder->axis);
    		printf("    Diameter: %f\n", cylinder->diameter);
    		printf("    Height: %f\n", cylinder->height);
    		printf("    Color: ");
    		print_color(cylinder->color);
            current = current->next;
        }
    }
    else
        printf("  None\n");
	// **********************************************************************
}

void place_pixel_in_img_data(char *data, int pixel, t_color *color)
{
	data[pixel + 0] = color->blue;
	data[pixel + 1] = color->green;
	data[pixel + 2] = color->red;
	data[pixel + 3] = 0x00;
}

void fill_img(void *img)
{
	int bpp, sl, endian;
	char *data = mlx_get_data_addr(img, &bpp, &sl, &endian);
	printf("OK (bpp: %d, sizeline: %d endian: %d type: %d)\n",bpp,sl,endian,((t_img *)img)->type);
	t_color pink = {.red = 255, .green = 20, .blue = 147};
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			int pixel = (y * sl) + (x * (bpp / 8));
			place_pixel_in_img_data(data, pixel, &pink);
		}
	}
	for (int y = 0; y < 10; y++)
	{
		for (int x = 20; x < 30; x++)
		{
			int pixel = (y * sl) + (x * (bpp / 8));
			place_pixel_in_img_data(data, pixel, &pink);
		}
	}
	for (int y = 10; y < 40; y++)
	{
		for (int x = 10; x < 20; x++)
		{
			int pixel = (y * sl) + (x * (bpp / 8));
			place_pixel_in_img_data(data, pixel, &pink);
		}
	}
}