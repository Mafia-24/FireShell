/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:09 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:10 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*ft_lstnew(char *name, char *value, t_data *data)
{
	t_env	*new;

	(void)data;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		failure_exit(data);
	new->name = ft_strdup(name, data);
	new->value = ft_strdup(value, data);
	new->next = NULL;
	return (new);
}

void	add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	if (last)
		last->next = new;
}

void	increment_shell_level(t_data *data)
{
	char	*shell_level;
	char	*new_level;

	shell_level = get_env(ft_strdup("SHLVL", data), data);
	if (a_to_l(shell_level) < 0)
	{
		new_level = ft_itoa(-1, data);
		add_env(ft_strdup("SHLVL", data), new_level, data, '=');
	}
}

char	**get_2d_envs(t_data *data)
{
	t_env	*tmp;
	char	**envs;
	int		i;

	i = 0;
	tmp = data->envs;
	increment_shell_level(data);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envs = malloc((i + 1) * sizeof(char *));
	if (!envs)
		failure_exit(data);
	tmp = data->envs;
	i = 0;
	while (tmp)
	{
		envs[i++] = ft_strcat_equal(tmp->name, tmp->value, data);
		tmp = tmp->next;
	}
	envs[i] = NULL;
	return (envs);
}
