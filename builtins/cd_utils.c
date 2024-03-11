/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:51:08 by ymafaman            #+#    #+#             */
/*   Updated: 2024/03/11 02:13:32 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_lvd(t_data *data)
{
	int	i;

	i = 0;
	while (data->last_valid_dir[i])
		i++;
	data->last_valid_dir[i++] = '/';
	data->last_valid_dir[i++] = '.';
	data->last_valid_dir[i++] = '.';
	data->last_valid_dir[i] = '\0';
}

static void	skip_dotdot_part(char *formated, int *i, int *j)
{
	while (formated[*i])
		(*i)++;
	while (*i > 0)
	{
		if (formated[(*i) - 1] == '.' && formated[(*i) - 2] == '.'
			&& formated[(*i) - 3] == '/')
		{
			(*i) -= 3;
			(*j)++;
		}
		else
			break ;
	}
}

static char	*format_path(char *formated, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	skip_dotdot_part(formated, &i, &j);
	if (j == 0)
		return (formated);
	i--;
	while (i > 0 && j > 0)
	{
		if (formated[i] == '/')
			j--;
		if (j > 0)
			i--;
	}
	formated[i] = '\0';
	if (!formated[0])
		return (free(formated), ft_strdup("/", data));
	return (formated);
}

static bool	is_valid_dir(char *formated, t_data *data)
{
	DIR	*dir;

	dir = opendir(formated);
	if (dir)
	{
		closedir(dir);
		if (!chdir(formated))
		{
			free(formated);
			if (!getcwd(data->last_valid_dir, 1024))
				return (failure_exit(data), 0);
		}
		else
			return (free(formated), failure_exit(data), 0);
	}
	else
	{
		free(formated);
		perror("minishell: cd: ..");
		data->g_exit_code = 1;
	}
	return (1);
}

void	cd_prev(t_data *data, bool is_child)
{
	char	path[1024];
	char	*formated;

	if (!getcwd(path, 1024))
	{
		update_lvd(data);
		add_env(ft_strdup("PWD", data),
			ft_strdup(data->last_valid_dir, data), data, '=');
		formated = format_path(ft_strdup(data->last_valid_dir, data), data);
		if (!is_valid_dir(formated, data))
		{
			if (is_child)
				clear_exit(data, 1);
			return ;
		}
	}
	else
	{
		if (chdir("..") == -1)
			failure_exit(data);
		if (!getcwd(data->last_valid_dir, 1024))
			return (failure_exit(data));
	}
	data->g_exit_code = 0;
}
