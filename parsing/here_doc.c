/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:16:22 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:16:23 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static void	expand_line_vars(char **line, t_data *data, int i)
{
	char	*buffer;
	char	*sub_buffer;
	char	*expanded_env;

	buffer = ft_strdup("", data);
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (ft_isalnum((*line)[i + 1]) || (*line)[i
				+ 1] == '_'))
		{
			expanded_env = expand_env_hd(*line, &i, data);
			if (expanded_env)
			{
				sub_buffer = buffer;
				buffer = ft_strjoin(buffer, expanded_env, data);
				free(sub_buffer);
				free(expanded_env);
			}
		}
		else
			buffer = add_to_part(&buffer, (*line)[i++], data);
	}
	free(*line);
	*line = buffer;
}

void	rm_new_line(char **line, t_data *data)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	while ((*line)[i + 1])
		i++;
	new_line = (char *)malloc((i + 1) * sizeof(char));
	if (!new_line)
	{
		free(*line);
		failure_exit(data);
	}
	while (j != i)
	{
		new_line[j] = (*line)[j];
		j++;
	}
	new_line[j] = '\0';
	free(*line);
	*line = new_line;
}

void	read_till_limiter(char *limiter, char *exp_bool, int fd, t_data *data)
{
	char	*line;

	signal(SIGINT, (void (*)(int))hd_ctrl_c);
	line = readline("here_doc> ");
	while (line && !is_similar(line, limiter))
	{
		if (is_similar(exp_bool, "1"))
			expand_line_vars(&line, data, 0);
		if ((write(fd, line, ft_strlen(line)) == -1)
			|| (write(fd, "\n", 1) == -1))
		{
			perror("Error: ");
			failure_exit(data);
		}
		free(line);
		line = readline("here_doc> ");
	}
	free(line);
	signal(SIGINT, (void (*)(int))ctrl_c);
}

int	do_hd(char *limiter, char *exp_bool, t_data *data)
{
	int	w_fd;
	int	r_fd;

	w_fd = open("/tmp/.hd_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (w_fd == -1)
		failure_exit(data);
	r_fd = open("/tmp/.hd_tmp", O_RDONLY);
	if (r_fd == -1)
		failure_exit(data);
	unlink("/tmp/.hd_tmp");
	data->flag = 0;
	read_till_limiter(limiter, exp_bool, w_fd, data);
	if (close(w_fd) == -1)
	{
		perror("Error: ");
		failure_exit(data);
	}
	if (data->flag && (close(r_fd) == -1
			|| open ("/dev/stdout", O_RDWR) == -1))
	{
		perror("Error: ");
		failure_exit(data);
	}
	return (r_fd);
}
