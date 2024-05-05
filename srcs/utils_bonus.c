/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:05:41 by mburakow          #+#    #+#             */
/*   Updated: 2024/03/01 15:05:39 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_exec_path(char **path, char *cmd)
{
	char	*slashpath;
	char	*execpath;

	execpath = NULL;
	slashpath = NULL;
	while (*path)
	{
		slashpath = ft_strjoin(*path, "/");
		execpath = ft_strjoin(slashpath, cmd);
		if (access(execpath, X_OK) != -1)
			return (execpath);
		else
		{
			if (execpath)
				free(execpath);
			execpath = NULL;
		}
		path++;
	}
	if (!path)
		return (cmd);
	return (NULL);
}

char	**tok_path(char **envp)
{
	char	**path;

	path = NULL;
	while (*envp != 0)
	{
		if (ft_strnstr(*envp, "PATH", 5))
			break ;
		envp++;
	}
	if (*envp)
		path = ft_split(ft_substr(*envp, 5, ft_strlen(*envp)), ':');
	return (path);
}

int	wait_for(int *chlds)
{
	int	status;
	int	nc;

	nc = 0;
	while (chlds[nc])
	{
		waitpid(chlds[nc], &status, 0);
		nc++;
	}
	return (WEXITSTATUS(status));
}

void	switch_pipe_fds(int pfd[2][2])
{
	close(pfd[READ][READ]);
	close(pfd[READ][WRITE]);
	pfd[READ][READ] = pfd[WRITE][READ];
	pfd[READ][WRITE] = pfd[WRITE][WRITE];
	pipe(pfd[WRITE]);
}

void	close_pipes(int pfd[2][2])
{
	close(pfd[READ][READ]);
	close(pfd[WRITE][WRITE]);
	close(pfd[READ][WRITE]);
	close(pfd[WRITE][READ]);
}
