/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:25 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:26 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static t_command	get_command(char *command, int k, int l, t_data *data)
{
	t_pars_args	p_args;
	int			i;

	i = 0;
	p_args = init_struct(k, l, data);
	while (command[i] && !data->flag)
	{
		if (is_space(command[i]) && fluch_red_buffers(p_args.buffs,
				&(p_args.cmd), &l, data)
			&& fluch_arg_buffers(&(p_args.buffs[0]), &(p_args.cmd), &(p_args.k),
				data))
			skip_spaces(command, &i);
		redirection(&p_args, command, &i, data);
	}
	fluch_red_buffers(p_args.buffs, &(p_args.cmd), &(p_args.l), data);
	fluch_arg_buffers(&(p_args.buffs[0]), &(p_args.cmd), &(p_args.k), data);
	return (free(p_args.buffs[0]), free(p_args.buffs[1]), free(p_args.buffs[2]),
		free(p_args.buffs[3]), p_args.cmd);
}

static void	handle_cmds(t_command *commands, char **pipe_splited, t_data *data)
{
	int	i;

	i = 0;
	while (pipe_splited[i])
	{
		trim(&pipe_splited[i], data);
		if (is_similar(pipe_splited[i], "\"\"") || is_similar(pipe_splited[i],
				"\'\'"))
		{
			commands[i].red_num = 0;
			commands[i].args = realloc_args(NULL, -1, "", data);
		}
		else
			commands[i] = get_command(pipe_splited[i], -1, -1, data);
		if (commands[i].args)
			commands[i].cmd = ft_strdup(commands[i].args[0], data);
		else
			commands[i].cmd = NULL;
		commands[i].path[0] = '\0';
		free(pipe_splited[i]);
		i++;
	}
}

t_command	*pars_starter(char *line, t_data *data)
{
	char		**pipe_splited;
	t_command	*commands;
	int			i;

	i = 0;
	while (is_space (line[i]))
		i++;
	if (!line[0] || !line[i] || !initial_check(line, data))
		return (NULL);
	pipe_splited = ft_split_commands(line, '|', data);
	data->cmds_num = number_of_commands(pipe_splited);
	commands = (t_command *)malloc(data->cmds_num * sizeof(t_command));
	if (!commands)
		failure_exit(data);
	handle_cmds(commands, pipe_splited, data);
	free(pipe_splited);
	return (commands);
}
