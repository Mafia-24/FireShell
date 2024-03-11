/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:19:15 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:19:16 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

char	*ft_strcat_slash(char *str1, char *str2)
{
	char	*res;
	int		i;

	res = (char *)malloc((ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (*str2)
		res[i++] = *(str2++);
	res[i++] = '/';
	while (*str1)
		res[i++] = *(str1++);
	res[i] = '\0';
	return (res);
}

char	*ft_strcat_equal(char *str1, char *str2, t_data *data)
{
	char	*res;
	int		i;

	res = (char *)malloc((ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!res)
		failure_exit(data);
	i = 0;
	while (str1 && *str1)
		res[i++] = *(str1++);
	res[i++] = '=';
	while (str2 && *str2)
		res[i++] = *(str2++);
	res[i] = '\0';
	return (res);
}

void	skip_spaces(char *command, int *i)
{
	while (is_space(command[*i]))
		(*i)++;
}

void	*ft_memset(int **b, int *v, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
		b[i++] = v;
	return (b);
}

bool	is_num(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num && num[i])
	{
		if ((num[i] < '0' || num[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}
