/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:58 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:59 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static int	c_w_2(const char *str, char c)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			counter++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (counter + 1);
}

static int	l_w(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i + 1);
}

static char	*m_w(const char *str, char c, t_data *data)
{
	int		i;
	int		l;
	char	*word;

	i = 0;
	l = l_w(str, c);
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

char	**ft_split_2(const char *str, char c, t_data *data)
{
	int		i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	strs = (char **)malloc(c_w_2(str, c) * sizeof(char *));
	if (!strs)
		failure_exit(data);
	while (str[i])
	{
		if (str[i] != c)
		{
			strs[j++] = m_w(&str[i], c, data);
			if (!strs[j - 1])
				return (ft_free(strs, j - 1));
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (strs[j] = NULL, strs);
}
