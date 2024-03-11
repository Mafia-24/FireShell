# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymafaman <ymafaman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 02:19:22 by ymafaman          #+#    #+#              #
#    Updated: 2024/03/11 02:19:23 by ymafaman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC=cc

FLAGS=-Wall -Wextra -Werror

NAME=minishell

SRCS=minishell.c \
	parsing/new_parser.c parsing/parsing_helper_1.c parsing/parsing_helper_2.c parsing/parsing_helper_3.c parsing/parsing_helper_4.c parsing/expand.c parsing/here_doc.c \
	utils/strings_1.c utils/strings_2.c utils/strings_3.c utils/errors.c  utils/split_cmds.c \
	utils/split_cmds_utils.c utils/ft_split.c utils/cleaning.c utils/str_join.c  utils/atol.c \
	utils/ft_itoa.c utils/signals.c utils/ft_split_space.c utils/trim.c\
	builtins/run.c builtins/echo.c builtins/export.c builtins/pwd.c builtins/unset.c builtins/cd.c builtins/cd_utils.c builtins/cd_special.c builtins/env.c  builtins/exit.c\
	env/utils_env0.c env/utils_env1.c env/utils_env2.c env/utils_env3.c \
	execution/execution_starter.c execution/execution_doer.c execution/procs.c execution/redirection_doer.c execution/execution_utils.c execution/execution_bi.c\
	initial_check/initial.c initial_check/check_red.c initial_check/check_pip.c \

OBJS=$(SRCS:.c=.o)

all: $(NAME)
	@echo "\033[1;38;5;208mMINISHELL is ready 🔥\033[0m "
	
$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -lreadline  ${LDFLAGS} $(OBJS) -o $(NAME)
	@echo "\033[0;32mLINKING ...\033[0m"
	
%.o: %.c minishell.h
	@$(CC) $(FLAGS) ${CPPFLAGS} -c $< -o $@
	@echo "\033[0;33mCOMPILING\033[0m" $<

clean:
	@rm -f $(OBJS)
	@echo "\033[0;34mCLEANING object files\033[0m"
	
fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31mCLEANING binary file\033[0m"

re: fclean all

.PHONY: all clean