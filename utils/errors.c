/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:48 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:49 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	failure_exit(t_data *data)
{
	perror("minishell");
	clear_exit(data, 1);
}

void	no_dequote(void)
{
	write(2, "missing quote!\n", 15);
}
