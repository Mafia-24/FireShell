/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_doer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:32 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:33 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	extract_cmd_path(t_data *data, char *path_var, int i)
{
	char	**splited_path;
	int		j;
	char	*buffer;

	j = 0;
	buffer = NULL;
	splited_path = ft_split_2(path_var, ':', data);
	while (splited_path[j])
	{
		buffer = ft_strcat_slash(data->cmds[i].cmd, splited_path[j++]);
		if (!access(buffer, F_OK) && !access(buffer, X_OK))
			return (ft_strcpy(data->cmds[i].path, buffer));
		else if ((!access(buffer, F_OK) && access(buffer, X_OK) == -1))
		{
			put_str("minishell: ", 2);
			perror(data->cmds[i].cmd);
			clear_exit(data, 126);
		}
		free(buffer);
	}
	free (path_var);
	put_str ("minishell: ", 2);
	put_str (data->cmds[i].cmd, 2);
	put_str (": command not found\n", 2);
	clear_exit (data, 127);
}

void	find_cmd_path(t_data *data, int i)
{
	char	*path_var;

	path_var = NULL;
	if (ft_contain(data->cmds[i].cmd, '/'))
	{
		if ((!access(data->cmds[i].cmd, F_OK) && access(data->cmds[i].cmd,
					X_OK) == -1))
		{
			put_str("minishell: ", 2);
			perror(data->cmds[i].cmd);
			clear_exit(data, 126);
		}
		ft_strcpy(data->cmds[i].path, data->cmds[i].cmd);
	}
	else
	{
		path_var = get_env(ft_strdup("PATH", data), data);
		if (!path_var)
			ft_strcpy(data->cmds[i].path, data->cmds[i].cmd);
		else
			extract_cmd_path(data, path_var, i);
	}
	free(path_var);
}

void	exec_cmd(t_data *data, int i)
{
	if (run_builtin(data->cmds[i], data, 1, 1))
		clear_exit(data, 0);
	find_cmd_path(data, i);
	if (execve(data->cmds[i].path, data->cmds[i].args, get_2d_envs(data)) == -1)
	{
		if (errno == 8)
			return ;
		if (errno == 13)
		{
			put_str("minishell: ", 2);
			put_str(data->cmds[i].cmd, 2);
			put_str(": is a directory\n", 2);
		}
		else
		{
			put_str("minishell: ", 2);
			perror(data->cmds[i].cmd);
		}
		clear_exit(data, 127);
	}
}

void	do_cmd(t_data *data, int **pipes, int i)
{
	if (i == 0)
	{
		first_cmd_proc(data, pipes, i);
	}
	else if (i == data->cmds_num - 1)
	{
		last_cmd_proc(data, pipes, i);
	}
	else
	{
		mid_cmds_proc(data, pipes, i, i);
	}
	do_reds(data, i);
	if (data->cmds[i].cmd)
		exec_cmd(data, i);
	clear_exit(data, 0);
}
