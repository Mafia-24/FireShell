/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:49 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:50 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	sig_handle(int chld_state, int *signaled, t_data *data)
{
	if (WTERMSIG(chld_state) == SIGINT)
	{
		if (!*signaled)
			write(1, "\n", 1);
		*signaled = 1;
		data->g_exit_code = 130;
	}
	else if (WTERMSIG(chld_state) == SIGQUIT)
	{
		if (!*signaled)
			write(2, "Quit: 3\n", 8);
		*signaled = 1;
		data->g_exit_code = 131;
	}
}

void	parent_waiting(int *pids, t_data *data)
{
	int	i;
	int	chld_state;
	int	signaled;

	i = 0;
	signaled = 0;
	while (i < data->cmds_num)
	{
		if ((waitpid(pids[i], &chld_state, 0) == -1) && errno != ECHILD)
			failure_exit(data);
		if (WIFEXITED(chld_state))
			data->g_exit_code = WEXITSTATUS(chld_state);
		else if (WIFSIGNALED(chld_state))
			sig_handle(chld_state, &signaled, data);
		i++;
	}
}

static void	close_hd_read_fd(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->cmds[i].red_num)
	{
		if (data->cmds[i].red[j].hd_inp_fd != -1)
		{
			if (close(data->cmds[i].red[j].hd_inp_fd) == -1)
			{
				perror("Error: ");
				failure_exit(data);
			}
		}
		j++;
	}
}

void	parent_fds_closing(int **pipes, t_data *data, int i)
{
	if (data->cmds_num > 1)
	{
		if (i != data->cmds_num - 1 && i != 0)
		{
			if ((close(pipes[i][1]) == -1) || (close(pipes[i - 1][0]) == -1))
				failure_exit(data);
		}
		else if (i == 0)
		{
			if (close(pipes[i][1]) == -1)
				failure_exit(data);
		}
		else if (i == data->cmds_num - 1)
		{
			if (close(pipes[i - 1][0]) == -1)
				failure_exit(data);
		}
	}
	if (data->cmds_num >= 1)
		close_hd_read_fd(data, i);
}

int	**get_pipes(t_data *data)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc((data->cmds_num - 1) * sizeof(int *));
	if (!pipes)
		failure_exit(data);
	ft_memset(pipes, NULL, data->cmds_num - 1);
	i = 0;
	while (i < data->cmds_num - 1)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!pipes[i])
			failure_exit(data);
		i++;
	}
	i = 0;
	while (i < data->cmds_num - 1)
	{
		if (pipe(pipes[i]) == -1)
			failure_exit(data);
		i++;
	}
	return (pipes);
}
