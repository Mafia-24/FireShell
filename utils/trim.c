/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:19:18 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:19:19 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static bool	get_limits(char *command, int *start, int *end)
{
	int		i;

	i = 0;
	while (is_space(command[i]))
		(i)++;
	*start = i;
	if (command[*start] == '\0')
	{
		free(command);
		command = NULL;
		return (0);
	}
	i = ft_strlen(command) - 1;
	while (is_space(command[i]))
		i--;
	*end = i;
	return (1);
}

void	trim(char **command, t_data *data)
{
	int		i;
	int		start;
	int		end;
	char	*new_command;

	i = 0;
	if (!get_limits(*command, &start, &end))
		return ;
	new_command = (char *)malloc((end - start + 2) * sizeof(char));
	if (!new_command)
		failure_exit(data);
	while (start <= end)
	{
		new_command[i] = (*command)[start++];
		i++;
	}
	new_command[i] = '\0';
	free(*command);
	*command = new_command;
}
