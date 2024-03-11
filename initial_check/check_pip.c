/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:03 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:04 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static void	print_error_token(void)
{
	put_str("minishell: syntax error near unexpected token `", 2);
}

static bool	unexpected_pip(char *line, int i, t_data *data)
{
	if (line[i] == '|')
	{
		data->g_exit_code = 258;
		print_error_token();
		return (put_str("|'\n", 2), true);
	}
	return (false);
}

static bool	duble_pip(int pipes_num, t_data *data)
{
	if (pipes_num == 2)
	{
		data->g_exit_code = 258;
		print_error_token();
		return (put_str("|'\n", 2), true);
	}
	return (false);
}

static void	pip_in_quotes(char *line, int *i, int *pipes_num)
{
	char	quote;

	if (line[*i] == '\'' || line[*i] == '"')
	{
		*pipes_num = 0;
		quote = line[*i];
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
	}
}

bool	check_pipes(char *line, t_data *data)
{
	int	i;
	int	pipes_num;

	i = 0;
	pipes_num = 0;
	while (is_space(line[i]))
		i++;
	if (unexpected_pip(line, i, data))
		return (false);
	while (line[i])
	{
		if (line[i] == '|')
			if (duble_pip(++pipes_num, data))
				return (false);
		pip_in_quotes(line, &i, &pipes_num);
		if (!is_space (line[i]) && line[i] != '|')
			pipes_num = 0;
		i++;
	}
	i--;
	while (is_space(line[i]))
		i--;
	if (unexpected_pip(line, i, data))
		return (false);
	return (true);
}
