/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:33:23 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/09 15:33:24 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

typedef struct s_point
{
	double			x;
	double			y;
}			t_point;

typedef struct s_colored_point
{
	double			x;
	double			y;
	int				color;
}			t_colored_point;

typedef struct s_circle
{
	int				x;
	int				y;
	int				radius;
}			t_circle;

typedef struct s_rect
{
	int				x;
	int				y;
	int				width;
	int				height;
}			t_rect;

#endif