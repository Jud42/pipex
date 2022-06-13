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

static void	dup_fd(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

static void	close_fd(t_pipex *pipex)
{
	int i;

	i = -1;
	while (++i < pipex->nb_pipe)
		close(pipex->tube[i]);
}

static void	process_child(char **argv, char **envp, t_pipex pipex)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (pipex.i == 0)
			dup_fd(pipex.infile, pipex.tube[1]);
		else if (pipex.i == pipex.nb_cmd - 1)
			dup_fd(pipex.tube[(2 * pipex.i) - 2], pipex.outfile);
		else
			dup_fd(pipex.tube[(2 * pipex.i) - 2], pipex.tube[(pipex.i * 2) + 1]);
		close_fd(&pipex);
		pipex.cmd_arg = ft_split(argv[2 + pipex.i + pipex.here_doc], ' ');
		find_path(&pipex);
		execve(pipex.cmd, pipex.cmd_arg, envp);
		free_pipex(&pipex, CMD_ARG);
	}
}
void	pipex_process(int argc, char **argv, char **envp, t_pipex *pipex)
{
	(void) argc;
	pipex->i = -1;

	while (++(pipex->i) < pipex->nb_cmd)
		process_child(argv, envp, *pipex);	
	close_fd(pipex);
	waitpid(-1, NULL, 0);
}

