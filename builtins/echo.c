/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:14:33 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:14:36 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		if (arg[i + 1] == 'n')
			i++;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

static void	skip_n_option(char **args, int *i, int *n)
{
	while (args[*i] && is_n_option(args[*i]))
	{
		(*i)++;
		*n = 1;
	}
}

static void	print_space(char *next_param, int out_fd)
{
	if (next_param)
		put_str(" ", out_fd);
}

void	echo(char **args, t_data *data, int out_fd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	(void)data;
	skip_n_option(args, &i, &n);
	while (args[i])
	{
		put_str(args[i], out_fd);
		print_space(args[i + 1], out_fd);
		i++;
	}
	if (!n)
		put_str("\n", out_fd);
	data->g_exit_code = 0;
}
