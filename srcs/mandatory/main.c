/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:43:19 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/03 18:47:26 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	process_child(char **argv, char **env, t_pipex pip, int i)
{
	take_path(env, &pip);
	if (i = 0)
	{
		pip.cmd_arg = ft_split(argv[2], ' ');
		find_path(&pip);
		close(pip.fd[0]);
		dup2(pip.infile, 0);
		dup2(pip.fd[1], 1);
		execve(pip.cmd, pip.cmd_arg, env);
	}
	else 
	{
		pip.cmd_arg = ft_split(argv[3], ' ');
		find_path(&pip);
		close(pip.fd[1]);
		dup2(pip.fd[0], 0);
		dup2(pip.outfile, 1);
		execve(pip.cmd, pip.cmd_arg, env);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex pip;
	int	pid[2];
	
	if (argc != 5)
		return (0);
	pip.infile = open(argv[1], O_RDONLY);
	if (pip.infile < 0)
		msg_error("Error: infile");
	pip.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (pip.outfile < 0)
		msg_error("Error: outfile");
	if (pipe(pip.fd) < 0)
		msg_error("Error: pipe");
	pid[0] = fork();
	if (pid[0] < 0)
		msg_error("Error: fork");
	else if (pid == 0)
		process_child(argv, envp, pip, 0);
	pid[1] = fork();
	if (pid[1] < 0)
		msg_error("Error: fork");
	else if (pid == 0)
		process_child(argv, envp, pip, 1);
	close(pip.fd[0]);
	close(pip.fd[1]);
	free_pipex(&pip, ALL);
	return (0);
}
