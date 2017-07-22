/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 17:16:59 by mgonon            #+#    #+#             */
/*   Updated: 2017/07/20 21:05:06 by mgonon           ###   ########.fr       */
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

static void create_image(t_param params, t_point map)
{
    void    *img_ptr;
    char    *my_img_str;

    img_ptr = mlx_new_image(params.mlx, WIDTH, HEIGHT);
    my_img_str =  mlx_get_data_addr(img_ptr, &(params.bits_pp), &(params.size_line), &(params.endian));
    printf("size_line = %d\n", params.size_line);
}

static void	bind_points(t_param params, t_point p1, t_point p2, int color)
{
	int x;
	int y;

	x = abs(p2.x - p1.x);
	y = abs(p2.y - p1.y);
	params.sx = (p1.x < p2.x) ? 1 : -1;
	params.sy = (p1.y < p2.y) ? 1 : -1;
	params.counter = (x > y) ? (x / 2) : -(y / 2);
	while (1)
	{
		// mlx_pixel_put(params.mlx, params.win, p1.x, p1.y, color);
		mlx_pixel_put(params.mlx, params.win, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		params.e = params.counter;
		if (params.e > -x)
		{
			params.counter = params.counter - y;
			p1.x = p1.x + params.sx;
		}
		if (params.e < y)
		{
			params.counter = params.counter + x;
			p1.y = p1.y + params.sy;
		}
	}
}


static void calculate_iso(t_param params, t_point *map)
{
    int     x;
    int     y;
    t_point *first;

    first = map;
    params.height = HEIGHT;
    while (map)
    {
        params.width = WIDTH;
        while (map)
        {
            // printf("map->x = %d\n", map->x);
            // x = (map->x - map->y) + (params.width / 9);
            // y = (map->x + map->y) / 2 + params.height / 9;
            x = (map->x - map->y) * 8 + (params.width / 9);
            y = (map->x + map->y) * 16 + params.height / 18;
            map->x = x;
            map->y = y;
            map = map->right;
            params.width += 400;            
        }
        params.height += 400;        
        map = first->down;
        first = first->down;
    }
}

static void draw_map(t_param params, t_point *map)
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
                    bind_points(params, *map, *(map)->right, 0x00FFFFF);
                else
                    bind_points(params, *map, *(map)->right, 0x000000FF);
            }
            if (map->down->down)
            {
                if (!map->z)
                    bind_points(params, *map, *(map)->down, 0x00FFFFF);
                else
                    bind_points(params, *map, *(map)->down, 0x000000FF);
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

int         display_map(t_point *map)
{
    t_param params;

    params.mlx = mlx_init();
	params.height = HEIGHT;
    params.win = mlx_new_window(params.mlx, WIDTH, HEIGHT, "fdf");
    calculate_iso(params, map);
    draw_map(params, map);
    create_image(params, *map);
    mlx_loop(params.mlx);
    return (1);
}
            // if (!todel->z && !todel->down->z)
            // printf("todel->x = %d\n", todel->x);
            // printf("todel->down->x = %d\n", todel->down->x);