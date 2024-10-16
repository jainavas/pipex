/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:54:34 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/16 20:49:19 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	closeanddupinput(int fd[2])
{
	close(fd[WRITE_FD]);
	dup2(fd[READ_FD], STDIN_FILENO);
	close(fd[READ_FD]);
}

int	cmdcall2(t_pipex *var, char **cmd)
{
	if (!cmd)
		return (freepipex(var), -1);
	if (pipe(var->fd2) == -1)
		return (-1);
	var->pid = fork();
	if (var->pid == 0)
	{
		closeanddupinput(var->fd);
		closeanddupoutput(var->fd2);
		execve(var->path2, cmd, var->envp);
	}
	else
	{
		close(var->fd[WRITE_FD]);
		close(var->fd2[WRITE_FD]);
		close(var->fdout);
		return (fdtofile(var, var->output), 0);
	}
	return (0);
}

int	cmdcall(t_pipex *var, char **cmd)
{
	if (!cmd)
		return (freepipex(var), -1);
	if (pipe(var->fd) == -1)
		return (-1);
	var->pid = fork();
	if (var->pid == 0)
	{
		dup2(var->fdin, var->fd[READ_FD]);
		close(var->fdin);
		dup2(var->fd[WRITE_FD], STDOUT_FILENO);
		closeanddupinput(var->fd);
		execve(var->path, var->cmd, var->envp);
	}
	else
	{
		return (cmdcall2(var, var->cmd2));
	}
	return (0);
}

void	vardefs(t_pipex *vars, char **argv)
{
	vars->cmd = ft_split(argv[2], ' ');
	vars->cmd2 = ft_split(argv[3], ' ');
	vars->output = argv[4];
	vars->path = pathseek(vars->cmd, vars);
	if (!vars->path)
		return (freepipex(vars), exit(-1));
	vars->path[ft_strlen(vars->path) - 1] = '\0';
	vars->fdin = open(argv[1], O_RDONLY);
	vars->path2 = pathseek(vars->cmd2, vars);
	if (!vars->path2)
		return (freepipex(vars), exit(-1));
	vars->path2[ft_strlen(vars->path2) - 1] = '\0';
	vars->fdin = open(argv[1], O_RDONLY);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*vars;

	vars = ft_calloc(1, sizeof(t_pipex));
	vars->envp = envp;
	vardefs(vars, argv);
	if (checks(argv, argc, vars) != 0)
		return (freepipex(vars), -1);
	if (cmdcall(vars, vars->cmd) != 0)
		return (freepipex(vars), -1);
	freepipex(vars);
	return (0);
}
