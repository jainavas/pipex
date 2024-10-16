/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:20:50 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/16 20:47:16 by jainavas         ###   ########.fr       */
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
	{
		perror("pipe failed");
		return (NULL);
	}
	pid = fork();
	if (pid == 0)
	{
		closeanddupoutput(fd);
		execve("/usr/bin/which", argv, var->envp);
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

int	checks(char **argv, int argc, t_pipex *var)
{
	if (argc != 5)
		return (ft_putstr_fd("Num args mal\n", 1), -1);
	if (access(argv[1], R_OK) != 0)
		return (ft_putstr_fd("Primer arg inaccesible\n", 1), -1);
	if (access(var->path, X_OK) != 0)
		return (ft_putstr_fd("Segundo arg inejecutable\n", 1), -1);
	if (access(var->path2, X_OK) != 0)
		return (ft_putstr_fd("Tercer arg inejecutable\n", 1), -1);
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
}

void	closeanddupoutput(int fd[2])
{
	close(fd[READ_FD]);
	dup2(fd[WRITE_FD], STDOUT_FILENO);
	close(fd[WRITE_FD]);
}
