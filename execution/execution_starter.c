/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_starter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:37 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:38 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	exec_builting(t_data *data)
{
	int	out_fd;

	out_fd = do_single_bi_reds(data);
	if (out_fd == -42)
	{
		data->g_exit_code = 1;
		return ;
	}
	run_builtin(data->cmds[0], data, out_fd, 0);
	if (out_fd != 1 && close(out_fd) == -1)
		failure_exit(data);
}

void	sig_fork(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	exec_starter(t_data *data)
{
	int	i;

	if (data->cmds_num == 1 && is_a_builting(data->cmds[0].cmd))
		return (exec_builting(data));
	data->pipes = get_pipes(data);
	data->pids = (int *)malloc(data->cmds_num * sizeof(int));
	if (!data->pids)
		failure_exit(data);
	i = 0;
	while (i < data->cmds_num)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			failure_exit(data);
		if (data->pids[i] == 0)
		{
			sig_fork();
			do_cmd(data, data->pipes, i);
		}
		else
			parent_fds_closing(data->pipes, data, i);
		i++;
	}
	parent_waiting(data->pids, data);
	free_pids_pipes(&data->pids, &data->pipes, data->cmds_num);
}
