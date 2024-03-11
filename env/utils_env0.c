/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:05 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:06 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	set_unseted_envs(t_data *data)
{
	char	*pwd;
	char	*oldpwd;
	char	*shlvl;

	pwd = get_env(ft_strdup("PWD", data), data);
	oldpwd = get_env(ft_strdup("OLDPWD", data), data);
	shlvl = get_env(ft_strdup("SHLVL", data), data);
	if (!pwd)
		add_env(ft_strdup("PWD", data),
			ft_strdup(data->last_valid_dir, data), data, '=');
	if (!oldpwd)
		add_env(ft_strdup("OLDPWD", data),
			NULL, data, '=');
	if (shlvl == NULL || shlvl[0] == '\0')
		add_env(ft_strdup("SHLVL", data), ft_strdup("1", data), data, '=');
	else if (is_similar(shlvl, "999"))
		add_env(ft_strdup("SHLVL", data), ft_strdup("", data), data, '=');
	else
		add_env(ft_strdup("SHLVL", data),
			ft_itoa(a_to_l(shlvl) + 1, data), data, '=');
	free(pwd);
	free(oldpwd);
	free(shlvl);
}

void	init_env(t_data *data)
{
	if (!getcwd(data->last_valid_dir, 1024))
	{
		perror("");
		clear_exit(data, 1);
	}
	set_unseted_envs(data);
}

void	setup_env(char **env, t_data *data)
{
	int		i;
	t_env	*envs;
	t_env	*new;
	char	*name;
	char	*value;

	envs = NULL;
	i = -1;
	while (env && env[++i])
	{
		get_name(&name, env[i], data);
		get_value(&value, env[i], data);
		new = ft_lstnew(name, value, data);
		free(name);
		free(value);
		add_back(&envs, new);
	}
	data->envs = envs;
	init_env(data);
}

void	clear_env(t_env *envs)
{
	t_env	*tmp;

	while (envs)
	{
		tmp = envs;
		envs = envs->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

char	*get_env(char *name, t_data *data)
{
	t_env	*tmp;

	tmp = data->envs;
	while (tmp)
	{
		if (is_similar(tmp->name, name))
			return (free(name), ft_strdup(tmp->value, data));
		tmp = tmp->next;
	}
	free(name);
	return (NULL);
}
