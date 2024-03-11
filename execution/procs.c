/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:53 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:54 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	first_cmd_proc(t_data *data, int **pipes, int i)
{
	if (data->cmds_num == 1)
		return ;
	if (dup2(pipes[i][1], 1) == -1)
	{
		failure_exit(data);
	}
	i = 0;
	while (i < data->cmds_num - 1)
	{
		if ((close(pipes[i][0]) == -1) || (close(pipes[i][1]) == -1))
			failure_exit(data);
		i++;
	}
}

void	mid_cmds_proc(t_data *data, int **pipes, int i, int j)
{
	if ((dup2(pipes[i][1], 1) == -1) || (dup2(pipes[i - 1][0], 0) == -1))
		failure_exit(data);
	while (i < data->cmds_num - 1)
	{
		if (close(pipes[i][1]) == -1)
			failure_exit(data);
		i++;
	}
	while (j < data->cmds_num)
	{
		if (close(pipes[j - 1][0]) == -1)
			failure_exit(data);
		j++;
	}
}

void	last_cmd_proc(t_data *data, int **pipes, int i)
{
	if (dup2(pipes[i - 1][0], 0) == -1)
		failure_exit(data);
	if ((close(pipes[i - 1][0]) == -1))
		failure_exit(data);
}

bool	is_a_builting(char *cmd)
{
	if (is_similar(cmd, "pwd") || is_similar(cmd, "cd") || is_similar(cmd,
			"exit") || is_similar(cmd, "echo") || is_similar(cmd, "export")
		|| is_similar(cmd, "env") || is_similar(cmd, "unset"))
		return (1);
	return (0);
}
