/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:19:01 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:19:02 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

char	**ft_split_commands(char *s, char c, t_data *data)
{
	char	**spliten;
	int		start;
	int		end;
	int		i;

	i = 0;
	spliten = (char **)malloc((count_strings(s, c) + 1) * sizeof(char *));
	if (!spliten)
		failure_exit(data);
	start = 0;
	end = 0;
	while (i < count_strings(s, c))
	{
		get_start_end(&start, &end, s, c);
		spliten[i] = (char *)malloc((end - start + 1) * sizeof(char));
		if (!spliten[i])
		{
			free_mem(spliten, i);
			failure_exit(data);
		}
		copying(s, start, end - 1, spliten[i++]);
		start = end;
	}
	spliten[i] = NULL;
	return (spliten);
}
