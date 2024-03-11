/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:18:54 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:18:55 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	ctrl_c(int sig, t_data *data)
{
	static t_data	*e;

	if (sig == 42)
		e = data;
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		e->g_exit_code = 1;
	}
}

void	hd_ctrl_c(int sig, t_data *data)
{
	static t_data	*e;

	if (sig == 42)
		e = data;
	if (sig == SIGINT)
	{
		(void) sig;
		e->g_exit_code = 1;
		e->flag = 1;
		if (close (0) == -1)
			failure_exit(data);
	}
}

void	ctrl_d(char *line, t_data *data)
{
	if (!line)
	{
		write(2, "exit\n", 5);
		clear_exit(data, data->g_exit_code);
	}
	if (line[0])
		add_history(line);
}
