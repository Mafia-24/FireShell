/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:19:34 by ymafaman          #+#    #+#             */
/*   Updated: 2024/03/11 02:19:35 by ymafaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_redirection
{
	char			*type;
	char			*file_name;
	char			*delimiter;
	int				hd_inp_fd;
}					t_redirection;

typedef struct s_command
{
	char			*cmd;
	char			**args;
	t_redirection	*red;
	int				red_num;
	char			path[1024];
}					t_command;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			*line;
	t_env			*envs;
	t_command		*cmds;
	int				cmds_num;
	char			last_valid_dir[1024];
	int				**pipes;
	int				*pids;
	int				flag;
	int				g_exit_code;
}					t_data;

typedef struct s_pars
{
	int				k;
	int				l;
	t_command		cmd;
	char			*buffs[4];
}					t_pars_args;

// utils
int					ft_strlen(char *str);
bool				is_similar(char *s1, char *s2);
void				put_str(char *str, int fd);
char				*ft_strdup(char *str, t_data *data);
int					is_space(char c);
int					ft_isalnum(int c);
char				*ft_strjoin(char *s1, char *s2, t_data *data);
char				**ft_split_2(const char *str, char c, t_data *data);
char				**ft_split_space(const char *str, t_data *data);
void				clear_vector(char **vect);
long				a_to_l(char *str);
bool				is_num(char *status);
int					ft_strncmp(char *s1, char *s2, size_t n);
char				*ft_itoa(int n, t_data *data);
int					ft_contain(char *str, int c);
void				ft_strcpy(char *dest, const char *src);
char				*ft_strcat_equal(char *str1, char *str2, t_data *data);
char				*ft_strcat_slash(char *str1, char *str2);
void				ft_strlcpy(char *dst, const char *src, size_t size);
void				trim(char **command, t_data *data);
void				skip_spaces(char *command, int *i);
void				*ft_memset(int	**b, int *v, size_t num);
int					c_w(const char *str);
void				failure_exit(t_data *data);
void				no_dequote(void);

// split commands
char				**ft_split_commands(char *s, char c, t_data *data);
void				copying(char *str, int start, int end, char *dest);
void				skip_quotes(char *str, int *i);
int					count_strings(char *str, char c);
char				**free_mem(char **spliten, int i);
void				get_start_end(int *start, int *end, char *s, char c);

// cleaning
void				clear_cmds(t_data *data);
void				clear_exit(t_data *data, int status);

// parsing
void				ctrl_d(char *line, t_data *data);
void				ctrl_c(int sig, t_data *data);

t_command			*pars_starter(char *line, t_data *data);
char				*add_to_part(char **part, char c, t_data *data);
char				**realloc_args(char **args, int k, char *buffer,
						t_data *data);
void				clone_red(t_redirection *new_red, t_redirection **old_red,
						int l, t_data *data);
t_redirection		*realloc_red(t_redirection **red, int l, char *bufs[4],
						t_data *data);
void				get_redirection_args(char *command, int *i, char *bufs[4],
						t_data *data);
int					number_of_commands(char **commands);
void				add_whats_between_quotes(char **buffer, int *i,
						char *command, t_data *data);
void				add_whats_between_quotes_red(char *buffs[4], int *i,
						char *command, t_data *data);
void				init_buffers(char *bufs[4], int *cmd_num, t_data *data);
bool				fluch_red_buffers(char *bufs[4], t_command *cmd, int *l,
						t_data *data);
bool				fluch_arg_buffers(char **arg_buffer, t_command *cmd, int *k,
						t_data *data);
void				trim(char **command, t_data *data);
char				*expand_env(char *command, int *j, t_data *data);
char				*expand_env_hd(char *line, int *j, t_data *data);
char				*expand_first_env(char *command, int *j, t_data *data);
int					do_hd(char *limiter, char *exp_bool, t_data *data);

// helper 3 parse
void				get_expanded_arg(char ***arr, t_command *cmd, int *k,
						t_data *data);
char				***join_2d_bufs(char *command, int *i, t_data *data,
						char **arg_buff);
void				expand_g_exit_code(char **arg_buffer, int *i, t_data *data);
t_pars_args			init_struct(int k, int l, t_data *data);
void				redirection(t_pars_args *p_args, char *command, int *i,
						t_data *data);

//initial_check
bool				initial_check(char *line, t_data *data);
bool				check_red(char *line, t_data *data);
bool				check_pipes(char *line, t_data *data);

//env
void				setup_env(char **env, t_data *data);
void				clear_env(t_env *envs);
char				*get_env(char *name, t_data *data);
char				**get_2d_envs(t_data *data);

bool				get_name(char **name, char *arg, t_data *data);
bool				get_value(char **value, char *arg, t_data *data);
t_env				*ft_lstlast(t_env *lst);
t_env				*ft_lstnew(char *name, char *value, t_data *data);
void				add_back(t_env **lst, t_env *new);
void				add_env(char *name, char *value, t_data *data,
						char ex_case);

// builtins
bool				run_builtin(t_command command, t_data *data, int out_fd,
						bool is_child);
void				echo(char **args, t_data *data, int out_fd);
void				export(char **args, t_data *data, int out_fd);
void				pwd(t_data *data, int out_fd);
char				*get_cwd(t_data *data);
void				cd(char *path, bool is_child, t_data *data);
void				cd_prev(t_data *data, bool is_child);
bool				go_home(char *path, char **new_path, t_data *data);
void				unset(char **args, t_data *data);
void				env(t_data *data, int out_fd);
void				bi_exit(char **g_exit_code, t_data *data);

// redirections
void				open_inp_file(t_data *data, int i, int j);
void				open_out_file_tr(t_data *data, int i, int j);
void				open_out_file_ap(t_data *data, int i, int j);
void				dup_hd_file(t_data *data, int i, int j);
void				do_reds(t_data *data, int i);

// execution
void				exec_starter(t_data *data);
void				do_cmd(t_data *data, int **pipes, int i);
void				last_cmd_proc(t_data *data, int **pipes, int i);
void				mid_cmds_proc(t_data *data, int **pipes, int i, int j);
void				first_cmd_proc(t_data *data, int **pipes, int i);
void				do_reds(t_data *data, int i);
int					do_single_bi_reds(t_data *data);

// execution utils
void				parent_waiting(int *pids, t_data *data);
void				parent_fds_closing(int **pipes, t_data *data, int i);
int					**get_pipes(t_data *data);
bool				is_a_builting(char *cmd);
void				free_pids_pipes(int **pids, int ***pipes, int args_num);

//here_doc
void				hd_ctrl_c(int sig, t_data *data);
bool				is_a_builting(char *cmd);

#endif
