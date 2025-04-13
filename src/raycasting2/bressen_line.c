/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bressen_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:00:26 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/12 20:44:14 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void    ft_drawlinex(t_img  *img, t_point start, t_point    end, int    color)
{
    int index[4];
    index[2] = end.x - start.x;
    index[3] = end.y - start.y;
    index[1] = 1;
    if (index[3] < 0)
    {
        index[1] = -1;
        index[3] = -index[3];
    }
    index[0] = (2 *index[3]) - index[2];
    while (start.y < end.y)
    {
        my_mlx_pixel_put(img, start.x, start.y, color);
        if (index[0] > 0)
        {
            start.x += index[1];
            index[0] += 2 * (index[2] - index[3]);
        }
        else
            index[0] += 2 * index[2];
        start.y++;
    }
}

long    absolute(long n)
{
    if (n < 0)
        return (-n);
    return (n);
}

void help_for_draw(t_img *img, t_point start, t_point end, int color)
{
    if (start.y > end.y)
    {
        ft_swap(&start.x, &end.x);
        ft_swap(&start.y, &end.y);
        ft_drawliney(img, start, end, color);
    }
    else
        ft_drawliney(img, start, end, color);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    int offset;

    if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT || x <= 0 || y <= 0)
        return;
    offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
    dst = img->address + offset;
    *(unsigned int *)dst = color;
}