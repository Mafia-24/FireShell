/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_doer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 00:49:34 by ymafaman          #+#    #+#             */
/*   Updated: 2024/02/25 15:27:01 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_inp_file(t_data *data, int i, int j)
{
	int	fd;

	if (data->cmds[i].red[j].file_name == NULL)
	{
		put_str("minishell: ambiguous redirect\n", 2);
		clear_exit(data, 1);
	}
	if (access(data->cmds[i].red[j].file_name, F_OK) == -1
		|| access(data->cmds[i].red[j].file_name, R_OK) == -1)
	{
		put_str("minishell: ", 2);
		perror(data->cmds[i].red[j].file_name);
		clear_exit(data, 1);
	}
	fd = open(data->cmds[i].red[j].file_name, O_RDONLY);
	if (fd == -1)
		failure_exit(data);
	if ((dup2(fd, 0) == -1 || close(fd) == -1))
		failure_exit(data);
}

void	open_out_file_tr(t_data *data, int i, int j)
{
	int	fd;

	if (data->cmds[i].red[j].file_name == NULL)
	{
		put_str("minishell: ambiguous redirect\n", 2);
		clear_exit(data, 1);
	}
	if (!access(data->cmds[i].red[j].file_name, F_OK)
		&& (access(data->cmds[i].red[j].file_name, W_OK) == -1))
	{
		put_str("minishell: ", 2);
		perror(data->cmds[i].red[j].file_name);
		clear_exit(data, 1);
	}
	fd = open(data->cmds[i].red[j].file_name,
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		failure_exit(data);
	if ((dup2(fd, 1) == -1 || close(fd) == -1))
		failure_exit(data);
}

void	open_out_file_ap(t_data *data, int i, int j)
{
	int	fd;

	if (data->cmds[i].red[j].file_name == NULL)
	{
		put_str("minishell: ambiguous redirect\n", 2);
		clear_exit(data, 1);
	}
	if (!access(data->cmds[i].red[j].file_name, F_OK)
		&& (access(data->cmds[i].red[j].file_name, W_OK) == -1))
	{
		put_str("minishell : ", 2);
		perror(data->cmds[i].red[j].file_name);
		clear_exit(data, 1);
	}
	fd = open(data->cmds[i].red[j].file_name,
			O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		failure_exit(data);
	if ((dup2(fd, 1) == -1 || close(fd) == -1))
		failure_exit(data);
}

void	dup_hd_file(t_data *data, int i, int j)
{
	if ((dup2(data->cmds[i].red[j].hd_inp_fd, 0) == -1))
	{
		failure_exit(data);
	}
	if (close(data->cmds[i].red[j].hd_inp_fd) == -1)
	{
		failure_exit(data);
	}
}

void	do_reds(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->cmds[i].red_num)
	{
		if (is_similar(data->cmds[i].red[j].type, "<"))
			open_inp_file(data, i, j);
		else if (is_similar(data->cmds[i].red[j].type, ">"))
			open_out_file_tr(data, i, j);
		else if (is_similar(data->cmds[i].red[j].type, ">>"))
			open_out_file_ap(data, i, j);
		else if (is_similar(data->cmds[i].red[j].type, "<<"))
			dup_hd_file(data, i, j);
		j++;
	}
}
