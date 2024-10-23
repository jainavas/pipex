/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:20:50 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/23 20:31:35 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freepipex(t_pipex *vars)
{
	freedoublepointer(vars->cmd);
	freedoublepointer(vars->cmd2);
	free(vars->path);
	free(vars->path2);
	free(vars);
}

char	*pathseek(char **args, t_pipex *var)
{
	int			fd[2];
	int			pid;
	char		*tmp;
	char *const	argv[] = {"which", args[0], NULL};

	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		closeanddupoutput(fd);
		if (execve("/usr/bin/which", argv, var->envp) == -1)
			return (NULL);
	}
	else
	{
		close(fd[WRITE_FD]);
		wait(NULL);
		tmp = get_next_line(fd[READ_FD]);
		return (close(fd[READ_FD]), tmp);
	}
	return (NULL);
}

int	checks(char **argv, t_pipex *var)
{
	if (access(argv[1], R_OK) != 0)
		return (-1);
	if (!var->path || access(var->path, X_OK) != 0)
		return (-1);
	if (!var->path || access(var->path2, X_OK) != 0)
		return (-1);
	return (0);
}

void	fdtofile(t_pipex *var, char *filename)
{
	var->fdout = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	var->buf = get_next_line(var->fd2[READ_FD]);
	while (var->buf)
	{
		write(var->fdout, var->buf, ft_strlen(var->buf));
		free(var->buf);
		var->buf = get_next_line(var->fd2[READ_FD]);
	}
	close(var->fdout);
	close(var->fd2[READ_FD]);
}

void	closeanddupoutput(int fd[2])
{
	close(fd[READ_FD]);
	dup2(fd[WRITE_FD], STDOUT_FILENO);
	close(fd[WRITE_FD]);
}
