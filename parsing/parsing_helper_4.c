/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:37:13 by ymafaman          #+#    #+#             */
/*   Updated: 2024/02/17 13:16:32 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	fluch_red_buffers(char *bufs[4],
						t_command *cmd,
						int *l,
						t_data *data)
{
	if (bufs[2])
	{
		cmd->red = realloc_red(&(cmd->red), (*l)++, bufs, data);
		free(bufs[1]);
		free(bufs[2]);
		free(bufs[3]);
		bufs[1] = NULL;
		bufs[2] = NULL;
		bufs[3] = ft_strdup("1", data);
		cmd->red_num++;
	}
	return (1);
}

bool	fluch_arg_buffers(char **arg_buffer,
						t_command *cmd,
						int *k,
						t_data *data)
{
	if ((*arg_buffer))
	{
		cmd->args = realloc_args(cmd->args, (*k)++, *arg_buffer, data);
		free(*arg_buffer);
		*arg_buffer = NULL;
	}
	return (1);
}

void	clone_red(t_redirection *new_red,
				t_redirection **old_red,
				int l,
				t_data *data)
{
	bool	free_old;

	if (l != -1)
		free_old = true;
	else
		free_old = false;
	while (l >= 0)
	{
		new_red[l].type = ft_strdup((*old_red)[l].type, data);
		new_red[l].file_name = ft_strdup((*old_red)[l].file_name, data);
		new_red[l].delimiter = ft_strdup((*old_red)[l].delimiter, data);
		new_red[l].hd_inp_fd = (*old_red)[l].hd_inp_fd;
		free((*old_red)[l].type);
		free((*old_red)[l].file_name);
		free((*old_red)[l].delimiter);
		l--;
	}
	if (free_old)
		free(*old_red);
}

t_redirection	*realloc_red(t_redirection **red,
							int l,
							char *bufs[4],
							t_data *data)
{
	t_redirection	*new_red;

	new_red = (t_redirection *)malloc((l + 2) * sizeof(t_redirection));
	if (!new_red)
		failure_exit(data);
	new_red[l + 1].hd_inp_fd = -1;
	new_red[l + 1].type = ft_strdup(bufs[2], data);
	if (is_similar(bufs[2], "<<"))
	{
		new_red[l + 1].delimiter = ft_strdup(bufs[1], data);
		new_red[l + 1].hd_inp_fd = do_hd(bufs[1], bufs[3], data);
		new_red[l + 1].file_name = NULL;
	}
	else
	{
		new_red[l + 1].delimiter = NULL;
		new_red[l + 1].file_name = ft_strdup(bufs[1], data);
	}
	clone_red(new_red, red, l, data);
	return (new_red);
}
