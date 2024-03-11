/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:14:57 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:14:58 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

bool	run_builtin(t_command command, t_data *data, int out_fd, bool is_child)
{
	if (is_similar(command.cmd, "echo"))
		return (echo(command.args + 1, data, out_fd), 1);
	else if (is_similar(command.cmd, "cd"))
		return (cd(command.args[1], is_child, data), 1);
	else if (is_similar(command.cmd, "pwd"))
		return (pwd(data, out_fd), 1);
	else if (is_similar(command.cmd, "export"))
		return (export(command.args + 1, data, out_fd), 1);
	else if (is_similar(command.cmd, "unset"))
		return (unset(command.args + 1, data), 1);
	else if (is_similar(command.cmd, "env"))
		return (env(data, out_fd), 1);
	else if (is_similar(command.cmd, "exit"))
		return (bi_exit(command.args, data), 1);
	return (0);
}
