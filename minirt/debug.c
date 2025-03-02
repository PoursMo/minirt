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
	printf("Lights:\n");
	if (scene->lights)
	{
		t_list *l = scene->lights;
		while (l)
		{
			t_light *light = l->content;
			printf("  Light:\n");
			printf("    Position: ");
			print_vector3(light->position);
			printf("    Brightness: %f\n", light->brightness);
			printf("    Color: ");
			print_color(light->color);
			l = l->next;
		}
	}
	else
		printf("  None\n");
	// **********************************************************************
	printf("Shapes:\n");
	if (scene->shapes)
	{
		t_list *l = scene->shapes;
		while (l)
		{
			t_shape *s = (t_shape *)l->content;
			if (s->type == SPHERE)
			{
				printf("  Sphere:\n");
				printf("    Position: ");
				print_vector3(s->data.sphere.position);
				printf("    Radius: %f\n", s->data.sphere.radius);
				printf("    Color: ");
				print_color(s->color);
				printf("    Texture: %p\n", s->texture);
				printf("    Bump Map: %p\n", s->bump_map);
			}
			else if (s->type == PLANE)
			{
				printf("  Plane:\n");
				printf("    Position: ");
				print_vector3(s->data.plane.position);
				printf("    Normal: ");
				print_vector3(s->data.plane.normal);
				printf("    Color: ");
				print_color(s->color);
				printf("    Texture: %p\n", s->texture);
				printf("    Bump Map: %p\n", s->bump_map);
			}
			else if (s->type == CYLINDER)
			{
				printf("  Cylinder:\n");
				printf("    Position: ");
				print_vector3(s->data.cylinder.position);
				printf("    Axis: ");
				print_vector3(s->data.cylinder.axis);
				printf("    Radius: %f\n", s->data.cylinder.radius);
				printf("    Height: %f\n", s->data.cylinder.height);
				printf("    Color: ");
				print_color(s->color);
				printf("    Texture: %p\n", s->texture);
				printf("    Bump Map: %p\n", s->bump_map);
			}
			else if (s->type == TORUS)
			{
				printf("  Torus:\n");
				printf("    Position: ");
				print_vector3(s->data.torus.position);
				printf("    Direction: ");
				print_vector3(s->data.torus.direction);
				printf("    Minor Radius: %f\n", s->data.torus.minor_radius);
				printf("    Major Radius: %f\n", s->data.torus.major_radius);
				printf("    Color: ");
				print_color(s->color);
				printf("    Texture: %p\n", s->texture);
				printf("    Bump Map: %p\n", s->bump_map);
			}
			else
			{
				printf("  Unknown shape\n");
			}
			l = l->next;
		}
	}
	else
		printf("  None\n");
	// **********************************************************************
}

t_color map_v3_to_color(t_vector3 v)
{
	t_color c;

	v = v3_normalize(v);
	c.red = (unsigned char)((v.x + 1.0f) * 0.5f * 255);
	c.green = (unsigned char)((v.y + 1.0f) * 0.5f * 255);
	c.blue = (unsigned char)((v.z + 1.0f) * 0.5f * 255);
	return (c);
}

