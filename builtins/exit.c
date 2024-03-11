/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:14:45 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:14:46 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static char	*get_real_arg(char *arg, t_data *data)
{
	int		i;
	int		len;
	char	*real_arg;

	i = 0;
	len = 0;
	if (arg[i] == '-')
	{
		len++;
		i++;
	}
	while (arg[i] == '0')
		i++;
	len += ft_strlen(arg + i);
	real_arg = (char *)malloc((len + 1) * sizeof(char));
	if (!real_arg)
		failure_exit(data);
	len = 0;
	if (arg[0] == '-')
		real_arg[len++] = '-';
	while (arg[i])
		real_arg[len++] = arg[i++];
	real_arg[len] = '\0';
	return (real_arg);
}

static int	is_a_huge_num(char *arg, t_data *data)
{
	char	*real_arg;

	real_arg = get_real_arg(arg, data);
	if (ft_strlen(real_arg) == 19)
	{
		if (ft_strncmp(real_arg, "9223372036854775807", 19) > 0)
		{
			return (free(real_arg), 1);
		}
	}
	else if (ft_strlen(real_arg) == 20)
	{
		if (ft_strncmp(real_arg, "-9223372036854775808", 20) > 0)
		{
			return (free(real_arg), 1);
		}
	}
	else if (ft_strlen(real_arg) > 20)
	{
		return (free(real_arg), 1);
	}
	return (free(real_arg), 0);
}

static bool	is_numeric(char *status)
{
	int	i;

	i = 0;
	if (status[i] == '+' || status[i] == '-')
		i++;
	while (status[i])
	{
		if (status[i] < '0' || status[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	bi_exit(char **args, t_data *data)
{
	write(2, "exit\n", 5);
	if (args[1] && (!is_numeric(args[1]) || is_a_huge_num(args[1], data)))
	{
		put_str("minishell: exit: ", 2);
		put_str(args[1], 2);
		put_str(": numeric argument required\n", 2);
		clear_exit(data, 255);
	}
	else if (args[1] && args[2])
	{
		data->g_exit_code = 1;
		put_str("minishell: exit: too many arguments\n", 2);
	}
	else if (args[1])
		clear_exit(data, (unsigned char)a_to_l(args[1]));
	else
		clear_exit(data, 0);
}
