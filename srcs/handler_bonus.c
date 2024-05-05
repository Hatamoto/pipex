/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:55:12 by mburakow          #+#    #+#             */
/*   Updated: 2024/03/01 16:23:35 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_heredoc(char *hd, int hdfd[2])
{
	char	*line;
	char	*eof;

	hd = ft_strdup(hd);
	eof = ft_strjoin(hd, "\n");
	line = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc> ", 2);
		line = get_next_line(0);
		if (ft_strnstr(line, eof, ft_strlen(line) + 1))
		{
			*ft_strnstr(line, eof, ft_strlen(line) + 1) = '\0';
			write(hdfd[WRITE], line, ft_strlen(line));
			close(hdfd[WRITE]);
			break ;
		}
		write(hdfd[1], line, ft_strlen(line));
	}
	free(eof);
	eof = NULL;
	free(line);
	line = NULL;
	return ;
}

void	handle_heredoc(char **argv, char **cmd_opt)
{
	int	hdfd[2];

	pipe(hdfd);
	get_heredoc(argv[2], hdfd);
	if (dup2(hdfd[READ], STDIN_FILENO) == -1)
		errexit("dup2 fail infile", cmd_opt[0], cmd_opt, 1);
	close(hdfd[READ]);
}

int	handle_infile(int heredoc, char **argv, char **cmd_opt)
{
	int	in_fd;

	if (heredoc)
		handle_heredoc(argv, cmd_opt);
	else if (access(argv[1], F_OK) < 0)
	{
		errmsg(ERR_NOSF, argv[1], cmd_opt, 1);
		return (1);
	}
	else
	{
		in_fd = open(argv[1], O_RDONLY);
		if (in_fd == -1)
		{
			errmsg(ERR_FPER, argv[1], cmd_opt, 1);
			return (1);
		}
		else if (dup2(in_fd, STDIN_FILENO) == -1)
			errexit("dup2 fail infile 2: ", argv[1], cmd_opt, 1);
		close(in_fd);
	}
	return (0);
}

void	handle_execve(char **cmd_opt, char **envp)
{
	char	**path;
	char	*cmdp;

	if (!cmd_opt || cmd_opt[0] == NULL || cmd_opt[0][0] == '\0')
		errexit(ERR_FPER, cmd_opt[0], cmd_opt, 127);
	else if (ft_strchr(cmd_opt[0], '/'))
		dir_check(cmd_opt, envp);
	else
	{
		path = tok_path(envp);
		if (!path)
			errexit(ERR_FPER, cmd_opt[0], cmd_opt, 127);
		cmdp = get_exec_path(path, cmd_opt[0]);
		if (cmdp == NULL)
			errexit(ERR_CMD, cmd_opt[0], cmd_opt, 127);
		if (!cmd_opt[0] || !*cmd_opt || !cmdp
			|| execve(cmdp, cmd_opt, envp) == -1)
		{
			free_args(&path);
			errexit(ERR_CMD, cmd_opt[0], cmd_opt, 127);
		}
	}
}

int	handle_outfile(char **argv, int i, char **cmd_opt)
{
	int	out_fd;

	out_fd = open(argv[i - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
	{
		errmsg(ERR_NOSF, argv[i - 1], cmd_opt, 1);
		return (2);
	}
	else if (dup2(out_fd, STDOUT_FILENO) == -1)
		errexit("dup2 fail outfile: ", argv[i - 1], cmd_opt, 1);
	close(out_fd);
	return (0);
}
