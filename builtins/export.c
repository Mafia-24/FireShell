/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:14:49 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:14:50 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

char	get_export_case(char *arg)
{
	while (*arg && *arg != '=' && *arg != '+')
		arg++;
	if (!(*arg))
		return ('=');
	return (*arg);
}

static void	export_print_env(t_data *data, int out_fd)
{
	t_env	*tmp;

	tmp = data->envs;
	while (tmp)
	{
		put_str("declare -x ", out_fd);
		put_str(tmp->name, out_fd);
		if (tmp->value)
		{
			put_str("=\"", out_fd);
			put_str(tmp->value, out_fd);
			put_str("\"", out_fd);
		}
		put_str("\n", out_fd);
		tmp = tmp->next;
	}
}

void	export(char **args, t_data *data, int out_fd)
{
	int		i;
	char	*name;
	char	*value;
	char	ex_case;

	data->g_exit_code = 0;
	i = 0;
	ex_case = 0;
	if (!args[0])
		export_print_env(data, out_fd);
	else
	{
		while (args[i])
		{
			if (get_name(&name, args[i], data) && get_value(&value, args[i],
					data))
			{
				ex_case = get_export_case(args[i]);
				add_env(name, value, data, ex_case);
			}
			else
				data->g_exit_code = 1;
			i++;
		}
	}
}
