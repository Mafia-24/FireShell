/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:01 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:02 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static inline void	similar_first(t_data *data, t_env *current, t_env *next)
{
	data->envs = next;
	free(current->name);
	free(current->value);
	free(current);
}

static inline void	similar_others(char *args, t_env *current, t_env *next)
{
	while (next)
	{
		if (is_similar(args, next->name))
		{
			current->next = next->next;
			free(next->name);
			free(next->value);
			free(next);
			break ;
		}
		current = next;
		next = current->next;
	}
}

static int	check_unset(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (put_str
			("minishell: unset: `': not a valid identifier\n", 2), 0);
	while (arg[i])
	{
		if (arg[0] >= '0' && arg[0] <= '9')
		{
			put_str("minishell: unset: `", 2);
			put_str(arg, 2);
			put_str("': not a valid identifier\n", 2);
			return (0);
		}
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			put_str("minishell: unset: `", 2);
			put_str(arg, 2);
			put_str("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	unset(char **args, t_data *data)
{
	int		i;
	t_env	*current;
	t_env	*next;

	i = -1;
	data->g_exit_code = 0;
	while (args[++i])
	{
		current = data->envs;
		next = current->next;
		if (!check_unset(args[i]))
			data->g_exit_code = 1;
		else if (is_similar(args[i], current->name))
			similar_first(data, current, next);
		else
			similar_others(args[i], current, next);
	}
}
