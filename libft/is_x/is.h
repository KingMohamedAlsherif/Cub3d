/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:05:42 by dehamad           #+#    #+#             */
/*   Updated: 2024/08/21 17:19:30 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_H
# define IS_H

# include "../libft.h"

int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
int	ft_isascii(int c);
int	ft_isprint(int c);
int	ft_issep(char s, char c);
int	ft_isspace(int c);
int	ft_issign(int c);
int	ft_isdifferent_sign(int num1, int num2);
int	ft_isempty_str(char *str);
int	ft_iselement_line(char *line);
int	ft_ismap_line(char *line);
int	ft_iswall(char *line);
int	ft_isletter(int c, int *counter);
int	ft_iscomma(int c, int *counter);
int	ft_istab(char *line);

#endif