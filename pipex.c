/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:54:34 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/17 16:45:12 by jainavas         ###   ########.fr       */
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
		return (-1);
	if (pipe(var->fd2) == -1)
		return (-1);
	var->pid = fork();
	if (var->pid == 0)
	{
		closeanddupinput(var->fd);
		closeanddupoutput(var->fd2);
		if (execve(var->path2, cmd, var->envp) == -1)
			return (-1);
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
		if (execve(var->path, var->cmd, var->envp) == -1)
			return (-1);
	}
	else
	{
		return (cmdcall2(var, var->cmd2));
	}
	return (0);
}

int	vardefs(t_pipex *vars, char **argv)
{
	vars->cmd = ft_split(argv[2], ' ');
	vars->cmd2 = ft_split(argv[3], ' ');
	vars->output = argv[4];
	vars->path = pathseek(vars->cmd, vars);
	if (!vars->path)
		return (ft_printf("zsh: command not found: %s\n", vars->cmd[0]), -1);
	vars->path[ft_strlen(vars->path) - 1] = '\0';
	vars->fdin = open(argv[1], O_RDONLY);
	if (vars->fdin == -1)
		return (ft_printf("zsh: no such file or directory: %s\n", argv[1]), -1);
	vars->path2 = pathseek(vars->cmd2, vars);
	if (!vars->path2)
		return (ft_printf("zsh: command not found: %s\n", vars->cmd2[0]), -1);
	vars->path2[ft_strlen(vars->path2) - 1] = '\0';
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*vars;

	vars = ft_calloc(1, sizeof(t_pipex));
	vars->envp = envp;
	if (argc != 5)
		return (free(vars), 0);
	if (vardefs(vars, argv) != 0)
		return (freepipex(vars), 127);
	if (checks(argv, vars) != 0)
		return (freepipex(vars), 127);
	if (cmdcall(vars, vars->cmd) != 0)
		return (freepipex(vars), 127);
	freepipex(vars);
	return (0);
}
