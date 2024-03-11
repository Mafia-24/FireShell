/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:19:29 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:19:30 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	set_up(t_data *data, char **env)
{
	rl_catch_signals = 0;
	setup_env(env, data);
	signal(SIGINT, (void (*)(int)) ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	data->line = NULL;
	data->pids = NULL;
	data->pipes = NULL;
	data->g_exit_code = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	set_up(&data, env);
	hd_ctrl_c(42, &data);
	ctrl_c(42, &data);
	while (1)
	{
		data.flag = 0;
		data.cmds_num = 0;
		data.line = readline("\033[0;38;5;208mminishell🔥\033[0m ");
		ctrl_d(data.line, &data);
		data.cmds = pars_starter(data.line, &data);
		if (data.cmds_num && !data.flag)
			exec_starter(&data);
		clear_cmds(&data);
		free(data.line);
	}
	return (0);
}
