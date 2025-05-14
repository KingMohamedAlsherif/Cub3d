/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:07:11 by amagoury          #+#    #+#             */
/*   Updated: 2024/03/30 05:54:57 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	if (!str)
		return (0);
	a = 0;
	while (str[a])
		a++;
	return (a);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s1;

	if (!s)
		return (NULL);
	i = 0;
	s1 = (char *)s;
	while (s1[i] != (unsigned char)c)
	{
		if (s1[i] == '\0' && c != '\0')
			return (0);
		i++;
	}
	return (s1 + i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	new = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!new)
		return (NULL);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	if (s2[j] == '\n')
		new[i] = '\n';
	new[i++] = '\0';
	if (s1)
		free (s1);
	return (new);
}
