/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:16:00 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/11 16:23:47 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void    *free_img(t_cub *cub, void *img)
{
    if (img)
    {
        mlx_destroy_image(cub->mlx, img);
    }
    return (NULL);
}

void    *free_win(void *mlx, void *win)
{
    if (win)
    {
        mlx_destroy_window(mlx, win);
    }
}

void    *cub_new_img(t_img  *img, void  *mlx, int   width, int   height)
{
    if (!img)
    {
        prirntf("Error\nImage not created\n");
        return (NULL);
    }
    if (img->img_ptr != NULL)
        mlx_destroy_image(mlx, img->img_ptr);
    img->img_ptr = mlx_new_image(mlx, width, height);
    if (!img->img_ptr)
        return (NULL);
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
    return (img);
}

void ft_swap(double *a, double *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}