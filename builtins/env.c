/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:14:40 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:14:41 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	env(t_data *data, int out_fd)
{
	t_env	*tmp;

	add_env(ft_strdup("_", data), ft_strdup("/usr/bin/env", data), data, '=');
	tmp = data->envs;
	while (tmp)
	{
		if (tmp->value)
		{
			put_str(tmp->name, out_fd);
			put_str("=", out_fd);
			put_str(tmp->value, out_fd);
			put_str("\n", out_fd);
		}
		tmp = tmp->next;
	}
	data->g_exit_code = 0;
}
