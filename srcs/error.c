/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:41:25 by mburakow          #+#    #+#             */
/*   Updated: 2024/03/01 16:14:55 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	errexit(const char *msg1, const char *msg2, char **cmd, int exitcode)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putendl_fd(msg2, 2);
	free_args(&cmd);
	exit(exitcode);
}

int	errmsg(const char *msg1, const char *msg2, char **cmd, int errcode)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putendl_fd(msg2, 2);
	free_args(&cmd);
	return (errcode);
}

void	dir_check(char **cmd_opt, char **envp)
{
	int	fd;

	if (!cmd_opt[0] || !*cmd_opt || execve(cmd_opt[0], cmd_opt, envp) == -1)
	{
		fd = open(cmd_opt[0], O_DIRECTORY);
		if (fd != -1)
			errexit(cmd_opt[0], ERR_ISDIR, cmd_opt, 126);
		errexit(ERR_NOSF, cmd_opt[0], cmd_opt, 127);
	}
	return ;
}

void	free_args(char ***args)
{
	int	i;

	if (!args || !*args)
		return ;
	i = 0;
	while ((*args)[i])
	{
		free((*args)[i]);
		(*args)[i] = NULL;
		i++;
	}
	free(*args);
	*args = NULL;
}
