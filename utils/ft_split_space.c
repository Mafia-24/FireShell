/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:54 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:55 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

int	c_w(const char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str && str[i])
	{
		if (!is_space(str[i]))
		{
			counter++;
			while (str[i] && !is_space(str[i]))
				i++;
		}
		else
			i++;
	}
	return (counter + 1);
}

static int	l_w(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_space(str[i]))
	{
		i++;
	}
	return (i + 1);
}

static char	*m_w(const char *str, t_data *data)
{
	int		i;
	int		l;
	char	*word;

	i = 0;
	l = l_w(str);
	word = (char *)malloc(l * sizeof(char));
	if (!word)
		failure_exit(data);
	while (i < l - 1)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **str, int j)
{
	while (j >= 0)
		free(str[j--]);
	free(str);
	return (NULL);
}

char	**ft_split_space(const char *str, t_data *data)
{
	int		i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	strs = (char **)malloc(c_w(str) * sizeof(char *));
	if (!strs)
		failure_exit(data);
	while (str[i])
	{
		if (!is_space(str[i]))
		{
			strs[j++] = m_w(&str[i], data);
			if (!strs[j - 1])
				return (ft_free(strs, j - 1));
			while (str[i] && !is_space(str[i]))
				i++;
		}
		else
			i++;
	}
	return (strs[j] = NULL, strs);
}
