/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:12 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:13 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static void	replace_env(char **ex_value, char *new_value, t_data *data)
{
	if (new_value == NULL)
		return ;
	free(*ex_value);
	*ex_value = ft_strdup(new_value, data);
	free(new_value);
}

static void	append_env(char **ex_value, char *new_value, t_data *data)
{
	char	*sub_ex_val;

	sub_ex_val = NULL;
	if (!new_value)
		return ;
	sub_ex_val = *ex_value;
	*ex_value = ft_strjoin(*ex_value, new_value, data);
	free(new_value);
	free(sub_ex_val);
}

void	add_env(char *name, char *value, t_data *data, char ex_case)
{
	t_env	*new;
	t_env	*tmp;

	tmp = data->envs;
	while (tmp)
	{
		if (is_similar(tmp->name, name))
		{
			free(name);
			if (ex_case == '=')
				return (replace_env(&tmp->value, value, data));
			else
				return (append_env(&tmp->value, value, data));
		}
		tmp = tmp->next;
	}
	new = ft_lstnew(name, value, data);
	if (!data->envs)
		data->envs = new;
	else
		ft_lstlast(data->envs)->next = new;
	free(name);
	free(value);
}
