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

static void init_pipex(int argc, char **argv, t_pipex *pip)
{
	pip->infile = open(argv[1], O_RDONLY);
	if (pip->infile < 0)
		msg_error("Error: ");
	pip->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (pip->outfile < 0)
		msg_error("Error: outfile");
	pip->path = NULL;
	pip->cmd_arg = NULL;
	pip->cmd = NULL;
}

static void	process_child(char **argv, char **env, t_pipex *pip, int i)
{

	if (i == 0)
	{
		pip->cmd_arg = ft_split(argv[2], ' ');
		find_path(pip);
		close(pip->fd[0]);
		dup2(pip->infile, 0);
		dup2(pip->fd[1], 1);
	}
	else 
	{
		pip->cmd_arg = ft_split(argv[3], ' ');
		find_path(pip);
		close(pip->fd[1]);
		dup2(pip->fd[0], 0);
		dup2(pip->outfile, 1);
	}
	execve(pip->cmd, pip->cmd_arg, env);
	close(pip->fd[0]);
	close(pip->fd[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex pip;
	int	pid[2];
	//int	stat;
	//int help_stat;

	if (argc != 5)
		return (0);
	init_pipex(argc, argv, &pip);
	if (pipe(pip.fd) < 0)
		msg_error("Error: pipe");
	take_path(envp, &pip);
	pid[0] = fork();
	if (pid[0] < 0)
		msg_error("Error: fork");
	else if (pid[0] == 0)
		process_child(argv, envp, &pip, 0);
	pid[1] = fork();
	if (pid[1] < 0)
		msg_error("Error: fork");
	else if (pid[1] == 0)
		process_child(argv, envp, &pip, 1);
	//waitpid(pid[0], NULL, 0);
	//if (WIFEXITED(stat))
	//	help_stat = WEXITSTATUS(stat);
	waitpid(1, NULL, 0);
	free_pipex(&pip, ALL);
	return (0);
}
