/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:55:27 by mburakow          #+#    #+#             */
/*   Updated: 2024/03/01 15:47:53 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define READ 0
# define WRITE 1

# define ERR_NOSF "no such file or directory: " 
# define ERR_FPER "permission denied: "
# define ERR_CMD "command not found: "
# define ERR_ISDIR ": is a directory"

typedef enum e_state
{
	BASIC,
	WORD,
	DSTRING,
	SSTRING
}				t_state;

typedef struct s_qsplit
{
	char		*str;
	char		*start;
	char		*p;
	t_state		state;
	int			c;
	int			count;
	char		**result;
}				t_qsplit;

int		handle_infile(int heredoc, char **argv, char **cmd_opt);
int		handle_outfile(char **argv, int i, char **cmd_opt);
void	handle_execve(char **cmd_opt, char **envp);
char	*get_exec_path(char **path, char *cmd);
char	**parse_quotes(char *str);
char	**tok_path(char **envp);
int		wait_for(int *chlds);
void	free_args(char ***args);
void	switch_pipe_fds(int pfd[2][2]);
void	close_pipes(int pfd[2][2]);
void	check_if_first(int i, char **cmd_opt);
int		errmsg(const char *msg1, const char *msg2, char **cmd, int errcode);
void	errexit(const char *msg1, const char *msg2, char **cmd, int exitcode);
void	check_if_dir(char **cmd_opt);
void	remove_slashes(char *input);
void	init_q(char *str, t_qsplit *q);
void	count_words(t_qsplit *q);
t_state	check_state(t_qsplit *q);
void	dir_check(char **cmd_opt, char **envp);

#endif