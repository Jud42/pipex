/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:43:19 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/14 21:29:43 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
static void close_fd(t_pipex *pip)
{
	close(pip->fd[0]);
	close(pip->fd[1]);
	close(pip->infile);
	close(pip->outfile);
}

static void init_pipex(int argc, char **argv, char **env, t_pipex *pip)
{
	pip->infile = open(argv[1], O_RDONLY);
	if (pip->infile < 0)
		msg_error("Error");
	pip->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pip->outfile < 0)
		msg_error("Error");
	take_path(env, pip); //take the all path exists//
	pip->cmd_arg = NULL;
	pip->cmd = NULL;
}

static void	process_child(char **argv, char **env, t_pipex pip)
{
	close(pip.fd[0]);
	dup2(pip.infile, 0);
	dup2(pip.fd[1], 1);
	pip.cmd_arg = ft_split(argv[2], ' ');
	find_path(&pip);
	execve(pip.cmd, pip.cmd_arg, env);
}

static void	process_parent(char **argv, char **env, t_pipex pip)
{
	close(pip.fd[1]);
	dup2(pip.fd[0], 0);
	dup2(pip.outfile, 1);
	pip.cmd_arg = ft_split(argv[3], ' ');
	find_path(&pip);
	execve(pip.cmd, pip.cmd_arg, env);
}



int	main(int argc, char *argv[], char *envp[])
{
	t_pipex pip;

	if (argc != 5)
	{
		write(2, "Bad argument\n", 13);
		exit(1);
	}
	init_pipex(argc, argv, envp, &pip);
	if (pipe(pip.fd) < 0)
		msg_error("Error: pipe");
	pip.pid = fork();
	if (pip.pid < 0)
		msg_error("Error: fork");
	else if (pip.pid == 0)
		process_child(argv, envp, pip);
	else
		process_parent(argv, envp, pip);
	close_fd(&pip);
	waitpid(pip.pid, NULL, 0);
	free_pipex(&pip, ALL);
	return (0);
}
