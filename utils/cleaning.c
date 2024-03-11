/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:22:32 by ymafaman          #+#    #+#             */
/*   Updated: 2024/02/17 13:35:19 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clear_reds(t_redirection *reds, int reds_num)
{
	int	i;

	i = 0;
	while (i < reds_num)
	{
		free(reds[i].type);
		free(reds[i].file_name);
		free(reds[i].delimiter);
		i++;
	}
	if (reds_num)
		free(reds);
}

void	clear_cmds(t_data *data)
{
	int			i;
	int			j;
	t_command	*cmds;

	i = 0;
	cmds = data->cmds;
	while (i < data->cmds_num)
	{
		j = 0;
		if (cmds[i].cmd)
		{
			while (cmds[i].args[j])
			{
				free(cmds[i].args[j]);
				j++;
			}
			free(cmds[i].args);
			free(cmds[i].cmd);
		}
		clear_reds(cmds[i].red, cmds[i].red_num);
		i++;
	}
	if (data->cmds_num != 0)
		free(cmds);
	data->cmds_num = 0;
}

void	free_pids_pipes(int **pids, int ***pipes, int args_num)
{
	int	i;

	i = 0;
	if (*pids)
	{
		free(*pids);
		*pids = NULL;
	}
	while (i < args_num - 1)
	{
		free((*pipes)[i]);
		i++;
	}
	free(*pipes);
	*pipes = NULL;
}

void	clear_exit(t_data *data, int status)
{
	rl_clear_history();
	clear_env(data->envs);
	clear_cmds(data);
	free(data->line);
	free_pids_pipes(&data->pids, &data->pipes, data->cmds_num);
	exit(status);
}
