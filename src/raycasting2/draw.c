/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:24:05 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/11 16:57:14 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_circle(t_img  *img, t_circle   circle, int color)
{
    int i;
    int j;
    int radius_squared;
    
    radius_squared = circle.radius * circle.radius;
    i = -circle.radius;
    while(i <= circle.radius)
    {
        j = -circle.radius;
        while (j <= circle.radius)
        {
            if ((i * i) + (j + j) <= radius_squared)
                my_mlx_pixel_put(img, circle.x + i, circle.y + j, color);
            j++;
        }
        i++;
    }
}

void draw_bressen_line(t_img *img, t_point start, t_point end, int color)
{
    int dx, dy;
    if (color == 0) color = 0xffffff; 
    dx = absolute(start.x - end.x);
    dy = absolute(start.y - end.y);
    if (dy < dx)
    {
        if (start.x > end.x)
        {
            ft_swap(&start.x, &end.x);
            ft_swap(&start.y, &end.y);
            ft_drawlinex(img, start, end, color);
        }
        else
            ft_drawlinex(img, start, end, color);
    }
    else
        help_for_draw(img, start, end, color);
}

void init_point(t_point *point, int x, int y)
{
    point->x = x;
    point->y = y;
}

void init_colored_point(t_colored_point *point, int x, int y, int color)
{
    point->x = x;
    point->y = y;
    point->color = color;
}

void init_circle(t_circle *circle, int x, int y, int radius)
{
    circle->radius = radius;
    circle->x = x;
    circle->y = y;
}