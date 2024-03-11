/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:15:26 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:15:27 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static int	trunc_red(char *filename, int *out_fd, t_data *data)
{
	int	fd;

	if (!access(filename, F_OK) && (access(filename, W_OK) == -1))
	{
		put_str("minishell : ", 2);
		perror(filename);
		return (-42);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		failure_exit(data);
	if (*out_fd != 1)
	{
		if (close(*out_fd) == -1)
			failure_exit(data);
	}
	*out_fd = fd;
	return (1);
}

static int	append(char *filename, int *out_fd, t_data *data)
{
	int	fd;

	if (!access(filename, F_OK) && (access(filename, W_OK) == -1))
	{
		put_str("minishell : ", 2);
		perror(filename);
		return (-42);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		failure_exit(data);
	if (*out_fd != 1)
	{
		if (close(*out_fd) == -1)
			failure_exit(data);
	}
	*out_fd = fd;
	return (1);
}

static int	input(char *filename, t_data *data)
{
	int	fd;

	if ((access(filename, F_OK) == -1) || (access(filename, R_OK) == -1))
	{
		put_str("minishell : ", 2);
		perror(filename);
		return (-42);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		failure_exit(data);
	if (close(fd) == -1)
		failure_exit(data);
	return (1);
}

int	do_single_bi_reds(t_data *data)
{
	int	out_fd;
	int	i;

	i = -1;
	out_fd = 1;
	while (++i < data->cmds[0].red_num)
	{
		if (is_similar(data->cmds[0].red[i].type, "<<"))
			continue ;
		if (!data->cmds[0].red[i].file_name)
			return (put_str("minishell: ambiguous redirect\n", 2), -42);
		else if (is_similar(data->cmds[0].red[i].type, ">"))
		{
			if (trunc_red(data->cmds[0].red[i].file_name, &out_fd, data) == -42)
				return (-42);
		}
		else if (is_similar(data->cmds[0].red[i].type, ">>"))
		{
			if (append(data->cmds[0].red[i].file_name, &out_fd, data) == -42)
				return (-42);
		}
		else if (input(data->cmds[0].red[i].file_name, data) == -42)
			return (-42);
	}
	return (out_fd);
}
