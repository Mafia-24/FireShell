/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:08 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:09 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static void	print_error_token(void)
{
	put_str("minishell: syntax error near unexpected token `", 2);
}

static bool	unexpected_token(char *line, int *i, t_data *data)
{
	while (is_space(line[*i]))
		(*i)++;
	if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
	{
		data->g_exit_code = 258;
		print_error_token();
		write(2, &line[*i], 1);
		put_str("'\n", 2);
		return (false);
	}
	if (!line[*i])
	{
		data->g_exit_code = 258;
		print_error_token();
		put_str("newline'\n", 2);
		return (false);
	}
	(*i)--;
	return (true);
}

bool	red_conflict(int count, char *line, int i, t_data *data)
{
	if ((count == 3) || ((i > 0) && (line[i] == '<' || line[i] == '>')
			&& (line[i - 1] != line[i])))
	{
		data->g_exit_code = 258;
		print_error_token();
		write(2, &line[i - 1], 1);
		put_str("'\n", 2);
		return (false);
	}
	return (true);
}

static void	skip_quoted_reds(int *i, char *line)
{
	int	j;

	j = *i;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		j++;
		while ((line[j] != line[*i]))
		{
			j++;
		}
		*i = j;
	}
}

bool	check_red(char *line, t_data *data)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (line[++i])
	{
		skip_quoted_reds (&i, line);
		count = 0;
		if (line[i] == '<' || line[i] == '>')
		{
			while (line[i] && (line[i] == '<' || line[i] == '>'))
			{
				i++;
				count++;
				if (!red_conflict(count, line, i, data))
					return (false);
			}
			if (!unexpected_token(line, &i, data))
				return (false);
		}
	}
	return (true);
}
