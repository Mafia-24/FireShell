/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:19:06 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:19:07 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	j;
	int	i;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	get_len(char *s1, char *s2)
{
	int	len;

	len = 1;
	while (*s1)
	{
		len++;
		s1++;
	}
	while (*s2)
	{
		len++;
		s2++;
	}
	return (len);
}

char	*ft_strjoin(char *s1, char *s2, t_data *data)
{
	char	*res;
	int		len;

	if (!s2 && s1)
		return (ft_strdup(s1, data));
	if (!s1 && s2)
		return (ft_strdup(s2, data));
	if (!s1 && !s2)
		return (ft_strdup("", data));
	len = get_len(s1, s2);
	res = (char *)malloc(len * sizeof(char));
	if (!res)
		failure_exit(data);
	*res = '\0';
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	return (res);
}
