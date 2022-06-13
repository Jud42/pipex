/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:43:19 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/03 18:47:24 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	process_child_one(char **argv, char **envp, t_pipex pipex)
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_arg = ft_split(argv[2], ' ');
	find_path(envp, &pipex);
	execve(pipex.cmd, pipex.cmd_arg, envp);
		//perror("error: execve_child_one");
}

static void	process_child_two(char **argv, char **envp, t_pipex pipex)
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_arg = ft_split(argv[3], ' ');
	find_path(envp, &pipex);
	execve(pipex.cmd, pipex.cmd_arg, envp);
		//perror("error: execve_child_two");
}

void	pipex_process(char **argv, char **envp, t_pipex *pipex)
{
	if (pipe(pipex->tube) < 0)
	{
		free_pipex(pipex);
		msg_error("Error: pipe");
	}
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		msg_error("Error: pid1");
	if (pipex->pid1 == 0)
		process_child_one(argv, envp, *pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		msg_error("Error: pid1");
	if (pipex->pid2 == 0)
		process_child_two(argv, envp, *pipex);
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}
