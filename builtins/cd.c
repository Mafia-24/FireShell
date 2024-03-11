/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:14:23 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:14:24 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static void	no_dir(char *new_path, bool is_child, t_data *data)
{
	put_str("minishell: cd: ", 2);
	perror(new_path);
	free(new_path);
	data->g_exit_code = 1;
	if (is_child)
		clear_exit(data, 1);
}

static void	no_cur(bool is_child, t_data *data)
{
	perror("cd: error retrieving current directory: \
getcwd: cannot access parent directories");
	data->g_exit_code = 1;
	if (is_child)
		clear_exit(data, 1);
}

void	cd_normal(char *path, t_data *data, bool is_child)
{
	DIR		*dir;
	char	*new_path;

	new_path = NULL;
	if (!go_home(path, &new_path, data))
	{
		if (is_child)
			clear_exit(data, 1);
		return ;
	}
	if (!new_path)
		new_path = ft_strdup(path, data);
	dir = opendir(new_path);
	if (!dir)
		return (no_dir(new_path, is_child, data));
	else
		closedir(dir);
	if (chdir(new_path) == -1)
		failure_exit(data);
	free(new_path);
	if (!getcwd(data->last_valid_dir, 1024))
		no_cur(is_child, data);
	data->g_exit_code = 0;
}

void	cd(char *path, bool is_child, t_data *data)
{
	char	*oldpwd;
	char	*cwd;

	if (path && path[0] == '\0')
		return ;
	oldpwd = ft_strdup("OLDPWD", data);
	cwd = get_cwd(data);
	if (is_similar(path, ".."))
		cd_prev(data, is_child);
	else
		cd_normal(path, data, is_child);
	add_env(ft_strdup(oldpwd, data), cwd, data, '=');
	free(oldpwd);
	add_env(ft_strdup("PWD", data),
		ft_strdup(data->last_valid_dir, data), data, '=');
}
