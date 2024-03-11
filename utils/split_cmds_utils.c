/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:18:58 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:18:59 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	copying(char *str, int start, int end, char *dest)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		dest[i] = str[start];
		i++;
		start = start + 1;
	}
	dest[i] = '\0';
}

void	skip_quotes(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while ((str[*i] != quote) && str[*i])
		(*i)++;
	(*i)++;
}

int	count_strings(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			while ((str[i] != c) && str[i])
			{
				if (str[i] == '\'' || str[i] == '"')
					skip_quotes(str, &i);
				else
					i++;
			}
			count++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

char	**free_mem(char **spliten, int i)
{
	while (i--)
		free(spliten[i]);
	free(spliten);
	return (NULL);
}

void	get_start_end(int *start, int *end, char *s, char c)
{
	char	quote;

	while (s[*start] == c)
		(*start)++;
	*end = *start;
	while (s[*end] != c && s[*end])
	{
		if (s[*end] == '\'' || s[*end] == '"')
		{
			quote = s[*end];
			(*end)++;
			while (s[*end] != quote && s[*end])
				(*end)++;
		}
		(*end)++;
	}
}
