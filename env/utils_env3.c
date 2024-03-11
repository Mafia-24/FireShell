/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:16 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:17 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static int	printf_export_err(char *arg)
{
	put_str("minishell: export: `", 2);
	put_str(arg, 2);
	put_str("': not a valid identifier\n", 2);
	return (0);
}

static int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_')
		return (1);
	return (0);
}

bool	get_name(char **name, char *arg, t_data *data)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]))
		return (printf_export_err(arg));
	*name = ft_strdup("", data);
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			free(*name);
			return (printf_export_err(arg));
		}
		*name = add_to_part(name, arg[i], data);
		i++;
	}
	if (arg[i] == '+' && arg[i + 1] != '=')
	{
		free(*name);
		return (printf_export_err(arg));
	}
	return (1);
}

bool	get_value(char **value, char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		*value = NULL;
	else
		*value = ft_strdup(arg + i + 1, data);
	return (1);
}
