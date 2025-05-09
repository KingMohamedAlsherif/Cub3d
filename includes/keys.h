/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:32 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/09 15:28:14 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H
#include <stdbool.h>


# define ESC 53
# define LEFT_AROW 123
# define RIGHT_AROW 124
# define DOWN_AROW 125
# define UP_AROW 126
# define ZOOM_IN 24
# define ZOOM_OUT 27
# define ONE 18
# define TWO 19
# define THREE 20
# define LOOP 37
# define W_KEY 13
# define D_KEY 2
# define S_KEY 1
# define A_KEY 0
# define MESH 46
# define NMESH 45
# define REDO 666
# define Z_KEY 6
# define X_KEY 7
# define F_KEY 3
# define PLUS_KEY 69
# define MINUS_KEY 78
# define SHIFT 258
# define Q_KEY 12
# define T_KEY 17
# define C_KEY 8
# define ENTER_KEY 36
# define NUMPAD_ENTER_KEY 76


typedef struct s_keys
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	scale_flag;
	bool	aim;
	bool	aim_released;
	bool	m_left;
	bool	m_right;
	bool	m_leftclick;
	bool	m_rightclick;
	bool	q;
	bool	t;
	bool	f;
	bool	c; /* controls */
}			t_keys;

#endif