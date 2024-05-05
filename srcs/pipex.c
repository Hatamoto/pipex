/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:54:50 by mburakow          #+#    #+#             */
/*   Updated: 2024/03/01 16:11:09 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_child(char **argv, int i[3], char **envp, int pfd[2][2])
{
	char	**cmd_opt;
	int		heredoc;
	int		ferror;

	heredoc = 0;
	ferror = 0;
	cmd_opt = parse_quotes(argv[i[0]]);
	if (!ft_strncmp("here_doc", argv[1], 9))
		heredoc = 1;
	if (i[0] == 2 + heredoc)
		ferror = handle_infile(heredoc, argv, cmd_opt);
	else if (dup2(pfd[READ][READ], STDIN_FILENO) == -1)
		exit(1);
	close(pfd[READ][READ]);
	if (i[0] == i[1] - 2)
		ferror = handle_outfile(argv, i[1], cmd_opt);
	else
	{
		if (dup2(pfd[WRITE][WRITE], STDOUT_FILENO) == -1)
			errexit("dup2 fail hchild2: ", cmd_opt[0], cmd_opt, 1);
	}
	close_pipes(pfd);
	if (!ferror)
		handle_execve(cmd_opt, envp);
}

static int	*fork_children(int i[3], int pfd[2][2], char **argv, char **envp)
{
	int	*chlds;
	int	pid;

	chlds = ft_calloc(i[1], sizeof(int *));
	if (!chlds)
		errexit("calloc chlds", NULL, NULL, 1);
	while (i[0] < i[1] - 1)
	{
		pid = fork();
		if (pid == -1)
		{
			wait_for(chlds);
			errexit("fork failure: ", NULL, NULL, 1);
		}
		if (pid == 0)
			handle_child(argv, i, envp, pfd);
		else
		{
			chlds[i[0] - i[2]] = pid;
			switch_pipe_fds(pfd);
		}
		i[0]++;
	}
	return (chlds);
}

int	handle_parent(int argc, char **argv, char **envp, int pfd[2][2])
{
	int	heredoc;
	int	*chlds;
	int	status;
	int	i[3];

	heredoc = 0;
	status = 0;
	if (!ft_strncmp("here_doc", argv[1], 9))
		heredoc = 1;
	i[0] = 2 + heredoc;
	i[1] = argc;
	i[2] = 2 + heredoc;
	chlds = fork_children(i, pfd, argv, envp);
	close_pipes(pfd);
	status = wait_for(chlds);
	if (chlds)
	{
		free(chlds);
		chlds = NULL;
	}
	return (status);
}

int	main(int argc, char *argv[], char **envp)
{
	int	pfd[2][2];
	int	status;

	if (argc != 5)
	{
		ft_printf("Wrong arg count.\n");
		return (errmsg("Usage: ", "./pipex inf cmd1 cmd2 outf.", NULL, 1));
	}
	if (pipe(pfd[0]) == -1)
		errexit("pipe 1", NULL, NULL, 1);
	if (pipe(pfd[1]) == -1)
		errexit("pipe 2", NULL, NULL, 1);
	status = handle_parent(argc, argv, envp, pfd);
	return (status);
}
