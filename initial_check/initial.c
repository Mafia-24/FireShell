/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:12 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:13 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static bool	check_quotes(char *line, t_data *data)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
			{
				i++;
			}
			if (!line[i])
			{
				put_str("Syntax error: No dequote!\n", 2);
				data->g_exit_code = 258;
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	initial_check(char *line, t_data *data)
{
	return (check_quotes(line, data)
		&& check_red(line, data)
		&& check_pipes(line, data));
}
