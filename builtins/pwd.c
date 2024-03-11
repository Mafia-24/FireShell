/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:14:53 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:14:54 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

char	*get_cwd(t_data *data)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
		return (ft_strdup(cwd, data));
	return (ft_strdup(data->last_valid_dir, data));
}

void	pwd(t_data *data, int out_fd)
{
	char	*cwd;

	cwd = get_cwd(data);
	put_str(cwd, out_fd);
	put_str("\n", out_fd);
	free(cwd);
	data->g_exit_code = 0;
}
