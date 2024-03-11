/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:18 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:19 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	expand(char *command, int *j, char **arg, t_data *data)
{
	char	*next_env;
	char	*sub_arg;

	next_env = NULL;
	sub_arg = *arg;
	next_env = expand_env(command, j, data);
	*arg = ft_strjoin(*arg, next_env, data);
	free(next_env);
	free(sub_arg);
}

char	*expand_env(char *command, int *j, t_data *data)
{
	char	*var_buff;
	char	*arg;

	var_buff = NULL;
	arg = NULL;
	(*j)++;
	while (command[*j] && (ft_isalnum(command[*j]) || command[*j] == '_'))
		var_buff = add_to_part(&var_buff, command[(*j)++], data);
	arg = get_env(var_buff, data);
	while (command[*j] && !is_space (command[*j]))
	{
		if (command[*j] == '$' && (ft_isalnum(command[*j + 1])
				|| command[*j + 1] == '_'))
			expand(command, j, &arg, data);
		else if (command[*j] == '"' || command[*j] == '\'')
		{
			add_whats_between_quotes(&arg, j, command, data);
			(*j)++;
		}
		else
			arg = add_to_part(&arg, command[(*j)++], data);
	}
	return (arg);
}

char	*expand_env_hd(char *line, int *j, t_data *data)
{
	char	*var_buff;
	char	*arg;

	var_buff = NULL;
	arg = NULL;
	(*j)++;
	while (line[*j] && (ft_isalnum(line[*j]) || line[*j] == '_'))
		var_buff = add_to_part(&var_buff, line[(*j)++], data);
	arg = get_env(var_buff, data);
	return (arg);
}

char	*expand_first_env(char *command, int *j, t_data *data)
{
	char	*var_buff;
	char	*arg;

	var_buff = NULL;
	(*j)++;
	while (command[*j] && (ft_isalnum(command[*j]) || command[*j] == '_'))
		var_buff = add_to_part(&var_buff, command[(*j)++], data);
	arg = get_env(var_buff, data);
	return (arg);
}
