/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:14:12 by ymafaman          #+#    #+#             */
/*   Updated: 2024/02/09 08:16:29 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

void	clear_vector(char **vect)
{
	int	i;

	i = 0;
	if (!vect)
		return ;
	while (vect[i])
	{
		free(vect[i]);
		i++;
	}
	free(vect);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 && *s2 && n)
	{
		if ((unsigned char)*s1 > (unsigned char)*s2)
			return (1);
		else if ((unsigned char)*s1 < (unsigned char)*s2)
			return (-1);
		s1++;
		s2++;
		n--;
	}
	if (*s1 && !(*s2) && n)
		return (1);
	else if (!(*s1) && *s2 && n)
		return (-1);
	return (0);
}

int	ft_contain(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
