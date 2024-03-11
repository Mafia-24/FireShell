/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:13:26 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:13:27 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static void	go_prev(char **new_path)
{
	DIR		*dir;

	dir = opendir(*new_path);
	if (dir)
	{
		closedir(dir);
		put_str(*new_path, 1);
		put_str("\n", 1);
	}
}

bool	go_home(char *path, char **new_path, t_data *data)
{
	if (path == NULL)
	{
		*new_path = get_env(ft_strdup("HOME", data), data);
		if (*new_path == NULL)
		{
			put_str("minishell: cd: HOME not set\n", 2);
			return (data->g_exit_code = 1, 0);
		}
	}
	else if (is_similar(path, "-"))
	{
		*new_path = get_env(ft_strdup("OLDPWD", data), data);
		if (*new_path == NULL)
		{
			put_str("minishell: cd: OLDPWD not set\n", 2);
			return (data->g_exit_code = 1, 0);
		}
		go_prev(new_path);
	}
	return (1);
}
