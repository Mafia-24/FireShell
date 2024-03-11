/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:19:09 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:19:10 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && *str)
	{
		str++;
		len++;
	}
	return (len);
}

bool	is_similar(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

void	put_str(char *str, int fd)
{
	int	i;

	i = -1;
	while (str && str[++i])
		write(fd, &str[i], 1);
}

char	*ft_strdup(char *str, t_data *data)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		failure_exit(data);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
