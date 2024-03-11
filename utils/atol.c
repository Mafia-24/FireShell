/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:43 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:44 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

long	a_to_l(char *str)
{
	long	res;
	int		sign;

	sign = 1;
	res = 0;
	if (!is_num(str))
		return (0);
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}
