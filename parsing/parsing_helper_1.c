/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:29 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:30 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

int	number_of_commands(char **commands)
{
	int	count;

	count = 0;
	while (commands[count])
	{
		count++;
	}
	return (count);
}

static void	freeing(char *expanded_env, char	*sub_buffer)
{
	if (expanded_env)
		free(sub_buffer);
	free(expanded_env);
}

void	add_whats_between_quotes(char **buffer, int *i, char *command,
		t_data *data)
{
	int		j;
	char	quote;
	char	*sub_buffer;
	char	*expanded_env;

	j = *i + 1;
	quote = command[*i];
	if (command[j] == command[*i])
		*buffer = add_to_part(buffer, '\0', data);
	while (command[j] && command[j] != command[*i])
	{
		if (command[j] == '$' && (ft_isalnum(command[j + 1])
				|| command[j + 1] == '_') && quote == '"')
		{
			expanded_env = expand_first_env(command, &j, data);
			sub_buffer = *buffer;
			*buffer = ft_strjoin(*buffer, expanded_env, data);
			freeing(expanded_env, sub_buffer);
		}
		else if (command[j] == '$' && command[j + 1] == '?')
			expand_g_exit_code(buffer, &j, data);
		else
			*buffer = add_to_part(buffer, command[j++], data);
	}
	*i = j;
}

void	add_whats_between_quotes_red(char *buffs[4],
	int *i, char *command, t_data *data)
{
	int		j;

	j = *i + 1;
	if (command[j] == command[*i])
	{
		buffs[1] = add_to_part(&buffs[1], '\0', data);
	}
	while (command[j] != command[*i])
	{
		buffs[1] = add_to_part(&buffs[1], command[j], data);
		j++;
	}
	*i = j;
	free(buffs[3]);
	buffs[3] = ft_strdup("0", data);
}

void	init_buffers(char *bufs[4], int *cmd_num, t_data *data)
{
	bufs[0] = NULL;
	bufs[1] = NULL;
	bufs[2] = NULL;
	bufs[3] = ft_strdup("1", data);
	*cmd_num = 0;
}
