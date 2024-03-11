/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:36 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:37 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	get_expanded_arg(char ***arr, t_command *cmd, int *k, t_data *data)
{
	char	**splited_var;
	char	*sub_buffer;
	int		i;

	i = 0;
	if (*arr[0] && (*arr[0][0] == ' '))
	{
		fluch_arg_buffers(arr[1], cmd, k, data);
	}
	splited_var = ft_split_space(*arr[0], data);
	free(*arr[0]);
	free(arr[0]);
	while (splited_var && splited_var[i])
	{
		sub_buffer = *arr[1];
		*arr[1] = ft_strjoin(*arr[1], splited_var[i], data);
		free(sub_buffer);
		sub_buffer = NULL;
		fluch_arg_buffers(arr[1], cmd, k, data);
		i++;
	}
	free(arr);
	clear_vector(splited_var);
}

char	***join_2d_bufs(char *command, int *i, t_data *data, char **arg_buff)
{
	char	***arr;
	char	**expanded_env;

	expanded_env = (char **)malloc(1 * sizeof(char *));
	if (!expanded_env)
		failure_exit (data);
	arr = (char ***)malloc(2 * sizeof(char **));
	if (!arr)
		failure_exit(data);
	*expanded_env = expand_env(command, i, data);
	arr[0] = expanded_env;
	arr[1] = arg_buff;
	return (arr);
}

void	expand_g_exit_code(char **arg_buffer, int *i, t_data *data)
{
	char	*sub_buffer;
	char	*code;

	sub_buffer = *arg_buffer;
	code = ft_itoa(data->g_exit_code, data);
	*arg_buffer = ft_strjoin(*arg_buffer, code, data);
	free(code);
	free(sub_buffer);
	(*i) += 2;
}

t_pars_args	init_struct(int k, int l, t_data *data)
{
	t_pars_args	pars_args;

	init_buffers(pars_args.buffs, &pars_args.cmd.red_num, data);
	pars_args.k = k;
	pars_args.l = l;
	pars_args.cmd.args = NULL;
	return (pars_args);
}

void	redirection(t_pars_args *p_args, char *command,
	int *i, t_data *data)
{
	if (command[*i] == '\'' || command[*i] == '"')
	{
		add_whats_between_quotes(&(p_args->buffs[0]), i, command, data);
		(*i)++;
	}
	else if (command[*i] == '<' || command[*i] == '>')
	{
		get_redirection_args(command, i, p_args->buffs, data);
		fluch_red_buffers(p_args->buffs, &(p_args->cmd), &p_args->l, data);
	}
	else if (command[*i] == '$' && (ft_isalnum(command[*i + 1]) || command[*i
				+ 1] == '_'))
		get_expanded_arg(join_2d_bufs(command, i, data, &(p_args->buffs[0])),
			&(p_args->cmd), &p_args->k, data);
	else if (command[*i] == '$' && command[*i + 1] == '?')
		expand_g_exit_code(&(p_args->buffs[0]), i, data);
	else if (command[*i] == '$' && (command[*i + 1] == '"'
			|| command[*i + 1] == '\''))
		(*i)++;
	else
		p_args->buffs[0] = add_to_part(&(p_args->buffs[0]),
				command[(*i)++], data);
}
