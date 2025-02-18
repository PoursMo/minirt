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
    if (scene->ambiant_light)
    {
        printf("Ambiant Light:\n");
        printf("  Ratio: %f\n", scene->ambiant_light->ratio);
        printf("  Color: ");
        print_color(scene->ambiant_light->color);
    }
    else
    {
        printf("Ambiant Light: None\n");
    }

    if (scene->camera)
    {
        printf("Camera:\n");
        printf("  Position: ");
        print_vector3(scene->camera->position);
        printf("  Direction: ");
        print_vector3(scene->camera->direction);
        printf("  FOV: %d\n", scene->camera->fov);
    }
    else
    {
        printf("Camera: None\n");
    }

    if (scene->light)
    {
        printf("Light:\n");
        printf("  Position: ");
        print_vector3(scene->light->position);
        printf("  Brightness: %f\n", scene->light->brightness);
        printf("  Color: ");
        print_color(scene->light->color);
    }
    else
    {
        printf("Light: None\n");
    }

    // if (scene->shapes)
    // {
    //     printf("Shapes:\n");
    //     t_list *current = scene->shapes;
    //     while (current)
    //     {
    //         // Assuming shapes are stored as void* and cast to appropriate type
    //         // You need to implement the logic to print each shape based on its type
    //         // For example, if you have a t_sphere:
    //         t_sphere *sphere = (t_sphere *)current->content;
    //         printf("  Sphere:\n");
    //         printf("    Position: ");
    //         print_vector3(sphere->position);
    //         printf("    Radius: %f\n", sphere->radius);
    //         printf("    Color: ");
    //         print_color(sphere->color);

    //         // Move to the next shape
    //         current = current->next;
    //     }
    // }
    // else
    // {
    //     printf("Shapes: None\n");
    // }
}