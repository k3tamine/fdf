/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 17:16:59 by mgonon            #+#    #+#             */
/*   Updated: 2017/07/23 01:15:22 by mgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// isoX = cartX - cartY;
// isoY = (cartX + cartY) / 2;
// x = (map->x - map->y) * 32;
// y = (map->x + map->y) * 64;


// procédure tracerSegment(entier x1, entier y1, entier x2, entier y2) est
//   déclarer entier dx, dy ;
//   déclarer entier e ; // valeur d’erreur
//   e  ← x2 - x1 ;        // -e(0,1)
//   dx ← e × 2 ;          // -e(0,1)
//   dy ← (y2 - y1) × 2 ;  // e(1,0)
//   tant que x1 ≤ x2 faire
//     tracerPixel(x1, y1) ;
//     x1 ← x1 + 1 ;  // colonne du pixel suivant
//     si (e ← e - dy) ≤ 0 alors  // erreur pour le pixel suivant de même rangée
//       y1 ← y1 + 1 ;  // choisir plutôt le pixel suivant dans la rangée supérieure
//       e ← e + dx ;  // ajuste l’erreur commise dans cette nouvelle rangée
//     fin si ;
//   fin faire ;
//   // Le pixel final (x2, y2) n’est pas tracé.
// fin procédure ;

// static void create_image(t_param params, t_point map)
// {
//     void    *img_ptr;
//     char    *img_str;

//     img_ptr = mlx_new_image(params.mlx, WIDTH, HEIGHT);
//     img_str =  mlx_get_data_addr(img_ptr, &(params.bits_pp), &(params.size_line), &(params.endian));
//     printf("size_line = %d\n", params.size_line);
// }


// static void fill_pixel(int x, int y, int color, t_param params)
// {
//     int				i;
// 	unsigned int	u;
// 	int				index;
//     int             sizecol;

//     i = 0;
// 	// if ((y >= params.height) || (x >= params.width) || x < 0 || y < 0)
// 	// 	return (0);
//     sizecol = params.bits_pp / 8;
//     printf("sizecol = %d\n", sizecol);
// 	index = y * params.size_line * sizecol + x * sizecol;
// 	u = mlx_get_color_value(params.mlx, 0X00FFFFFF);
// 	while (i < sizecol)
// 	{
// 		// if (params.endian == params.local_endian)
//             // printf("test = %c\n", params.img_str[index + i]);
//             printf("index + i = %d\n", index + i);
// 			params.img_str[index + i] = *(((char*)&u) + i);
// 		// else
// 		// 	params.data[index + i] = *(((char*)&u) + sizecol - i - 1);
// 		i++;
// 	}
// 	// return (0);
//         // printf("toto\n");
//         // printf("get color = %d\n", mlx_get_color_value(params.img_str, color));
//         // *(params.img_str + ((4 * x) + (4 * params.size_line * y))) = color;
// 		// *(params.img_str + ((4 * x) + (4 * params.size_line * y) + 1)) = color;
// 		// *(params.img_str + ((4 * x) + (4 * params.size_line * y) + 2)) = color;
// }

static void fill_pixel(int x, int y, int color, t_param *params)
{
    int	            pos_x;
	int	            pos_y;
    int             pos;
    int             alpha;


    params->red   = (color & 0x00ff0000) >> 16;
    params->green = (color & 0x0000ff00) >> 8;
    params->blue  = (color & 0x000000ff);
    // printf("red = %d, green = %d, blue = %d\n", red, green, blue);
	pos_x = y * (WIDTH * 4);
	pos_y = x * 4;
	if (y > 0 && y < WIDTH)
	{
		pos = pos_x + pos_y;
		if (pos > 0 && pos < (HEIGHT * WIDTH * 4))
		{
            params->img_str[pos] = params->blue;
			params->img_str[pos + 1] = params->green;
			params->img_str[pos + 2] = params->red;
			params->img_str[pos + 3] = params->alpha;
		}
	}
}


static void	bind_points(t_param *params, t_point p1, t_point p2, int color)
{
	int x;
	int y;

	x = abs(p2.x - p1.x);
	y = abs(p2.y - p1.y);
	params->sx = (p1.x < p2.x) ? 1 : -1;
	params->sy = (p1.y < p2.y) ? 1 : -1;
	params->counter = (x > y) ? (x / 2) : -(y / 2);
	while (1)
	{
        fill_pixel(p1.x, p1.y, color, params);
		// mlx_pixel_put(params->mlx, params->win, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		params->e = params->counter;
		if (params->e > -x)
		{
			params->counter = params->counter - y;
			p1.x = p1.x + params->sx;
		}
		if (params->e < y)
		{
			params->counter = params->counter + x;
			p1.y = p1.y + params->sy;
		}
	}
}

static void calculate_iso(t_param params, t_point *map)
{   
    int     x;
    int     y;
    t_point *first;

    first = map;
    while (map)
    {
        while (map)
        {
            // x = (map->x - map->y) + (params.width / 9);
            // y = (map->x + map->y) / 2 + params.height / 9;
            // printf("x = %d\n", x);
            // printf("y = %d\n", y);
            x = WIDTH / 2 + map->x
				* params.space * cos(params.deg) - map->y
				* params.space * cos(params.deg);
            y = HEIGHT / 2 + map->x
				* params.space * sin(params.deg) + map->y * params.space
				* sin(params.deg) - map->z * params.space;
            map->x = x;
            map->y = y;
            map = map->right;
        }
        map = first->down;
        first = first->down;
    }
}

static void draw_map(t_param *params, t_point *map)
{
    t_point *first;

    first = map;
    while (map->down)
    {
        while (map->right)
        {
            if (map->right->right)
            {
                if (!map->z)
                    bind_points(params, *map, *(map)->right, 0x00FFFFFF);
                else
                    bind_points(params, *map, *(map)->right, 0x00FFFFFF);
                    // bind_points(params, *map, *(map)->right, 0x00DF1A42);
            }
            if (map->down->down)
            {
                if (!map->z)
                    bind_points(params, *map, *(map)->down, 0x00FFFFFF);
                else
                    // bind_points(params, *map, *(map)->down, 0x00DF1A42);
                    bind_points(params, *map, *(map)->down, 0x00FFFFFF);
            }
            map = map->right;
        }
        map = first->down;
        first = first->down;
    }
}

// static void draw_lines(t_param params, t_point *map)
// {
//     t_point *first;

//     first = map;
//     while (map->down)
//     {
//         while (map->right->right)
//         {
//             if (!map->z)
//                 bind_points(params, *map, *(map)->right, 0x00FFFFF);
//             else
//                 bind_points(params, *map, *(map)->right, 0x000000FF);
//             map = map->right;
//         }
//         map = first->down;
//         first = first->down;
//     }
// }

// static void draw_columns(t_param params, t_point *map)
// {
//     t_point *first;

//     first = map;
//     while (map->right)
//     {
//         while (map->down->down)
//         {
//             if (!map->z)
//                 bind_points(params, *map, *(map)->down, 0x00FFFFF);
//             else
//                 bind_points(params, *map, *(map)->down, 0x000000FF);
//             map = map->down;
//         }
//         map = first->right;
//         first = first->right;
//     }
// }

static int  init_params(t_param *params)
{
    params->space = WIDTH / 50;
    params->deg = 0.5;
    params->alpha = 0;

    return (0);
}

static int handle_image(t_param *params)
{
    // DEL IMG HERE
    params->img_ptr = mlx_new_image(params->mlx, WIDTH, HEIGHT);
    params->img_str = mlx_get_data_addr(params->img_ptr, &(params->bits_pp), &(params->size_line), &(params->endian));
    calculate_iso(*params, params->map);
    draw_map(params, params->map);
    mlx_put_image_to_window(params->mlx, params->win, params->img_ptr, 0, 0);

    return (0);  
}

static int key_hook(int keycode, t_param *params)
{
    printf("deg = %f\n", params->deg);
    if (keycode == ECHAP)
        exit(1);
    if (keycode == UP)
        params->deg += 0.1;
    // handle_image(&params);
    return (0);
}



int         display_map(t_point *map)
{
    void    *img_ptr;
    t_param params;

    init_params(&params);
    params.mlx = mlx_init();
	params.height = HEIGHT;
    params.win = mlx_new_window(params.mlx, WIDTH, HEIGHT, "fdf");
    params.map = map;
    handle_image(&params);
    // params.img_ptr = mlx_new_image(params.mlx, WIDTH, HEIGHT);
    // params.img_str = mlx_get_data_addr(params.img_ptr, &(params.bits_pp), &(params.size_line), &(params.endian));
    // calculate_iso(params, map);
    // draw_map(&params, map);
    // mlx_put_image_to_window(params.mlx, params.win, params.img_ptr, 0, 0);
    mlx_key_hook(params.win, key_hook, &params);
    mlx_loop(params.mlx);
    return (1);
}