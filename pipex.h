/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:22:26 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/17 16:07:04 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ_FD 0
# define WRITE_FD 1

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft_ext/libft.h"
# include "libft_ext/ft_printf.h"

typedef struct pipex
{
	int		pid;
	int		fd[2];
	int		fdout;
	int		fdin;
	int		fd2[2];
	char	*path;
	char	*path2;
	char	*buf;
	char	*output;
	char	**cmd;
	char	**cmd2;
	char	**envp;
}	t_pipex;

void		freepipex(t_pipex *vars);
char		*pathseek(char **args, t_pipex *var);
void		closeanddupoutput(int fd[2]);
void		closeanddupinput(int fd[2]);
int			checks(char **argv, t_pipex *var);
void		fdtofile(t_pipex *var, char *filename);
int			cmdcall2(t_pipex *var, char **cmd);
int			cmdcall(t_pipex *var, char **cmd);
int			vardefs(t_pipex *vars, char **argv);

#endif