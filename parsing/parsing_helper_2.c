/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:33 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:34 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*add_to_part(char **part, char c, t_data *data)
{
	char	*new;
	int		i;

	new = (char *)malloc((ft_strlen(*part) + 2) * sizeof(char));
	if (!new)
		failure_exit(data);
	i = 0;
	while (*part && (*part)[i])
	{
		new[i] = (*part)[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	if (*part)
		free(*part);
	return (new);
}

char	**realloc_args(char **args, int k, char *buffer, t_data *data)
{
	bool	free_old;
	char	**new_args;

	if (k != -1)
		free_old = true;
	else
		free_old = false;
	new_args = (char **)malloc((k + 3) * sizeof(char *));
	if (!new_args)
		failure_exit(data);
	new_args[k + 2] = NULL;
	new_args[k + 1] = ft_strdup(buffer, data);
	while (k >= 0)
	{
		new_args[k] = ft_strdup(args[k], data);
		free(args[k]);
		k--;
	}
	if (free_old)
		free(args);
	return (new_args);
}

static void	skipper(char *command, int *i, char *bufs[4], t_data *data)
{
	while (command[*i] && (command[*i] == '<' || command[*i] == '>'))
		bufs[2] = add_to_part(&bufs[2], command[(*i)++], data);
	while (command[*i] && is_space(command[*i]))
		(*i)++;
}

static char	*get_file_name(char *buff, char *expanded_env, t_data *data)
{
	char	*sub;

	sub = NULL;
	if ((c_w(expanded_env)-1 == 1))
	{
		sub = ft_strjoin(buff, expanded_env, data);
		trim (&sub, data);
	}
	free(expanded_env);
	free(buff);
	return (sub);
}

void	get_redirection_args(char *command, int *i, char *bufs[4], t_data *data)
{
	skipper(command, i, bufs, data);
	while (command[*i] && !is_space(command[*i]) && command[*i] != '<'
		&& command[*i] != '>')
	{
		if (command[*i] == '\'' || command[*i] == '"')
		{
			if (!is_similar(bufs[2], "<<"))
				add_whats_between_quotes(&bufs[1], i, command, data);
			else
				add_whats_between_quotes_red(bufs, i, command, data);
		}
		else
		{
			if (command[*i] == '$' && !is_similar(bufs[2], "<<")
				&& (command[*i + 1] != '"' && command[*i + 1] != '\''))
			{
				bufs[1] = get_file_name(bufs[1],
						expand_env(command, i, data), data);
				(*i)--;
			}
			else if (command[*i + 1] != '"' && command[*i + 1] != '\'')
				bufs[1] = add_to_part(&bufs[1], command[*i], data);
		}
		(*i)++;
	}
}
