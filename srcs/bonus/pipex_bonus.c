/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:43:19 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/17 17:13:38 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	dup_fd(int in, int out, t_pipex *pip)
{
	if (dup2(in, 0) < 0)
	{
		free_pipex(pip, ALL);
		msg_error("Error dup2");
	}
	if (dup2(out, 1) < 0)
	{
		free_pipex(pip, ALL);
		msg_error("Error dup2");
	}
}

static void	close_fd(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->nb_pipe)
		close(pipex->tube[i]);
}

static int	process_child(char **argv, char **envp, t_pipex pipex)
{
	pipex.pid = fork();
	if (pipex.pid < 0)
		return (-1);
	else if (pipex.pid == 0)
	{
		if (pipex.i == 0)
			dup_fd(pipex.infile, pipex.tube[1], &pipex);
		else if (pipex.i == pipex.nb_cmd - 1)
			dup_fd(pipex.tube[(2 * pipex.i) - 2], pipex.outfile, &pipex);
		else
			dup_fd(pipex.tube[(2 * pipex.i) - 2], \
					pipex.tube[(pipex.i * 2) + 1], &pipex);
		close_fd(&pipex);
		pipex.cmd_arg = ft_split(argv[2 + pipex.i + pipex.here_doc], ' ');
		find_path(&pipex);
		if (execve(pipex.cmd, pipex.cmd_arg, envp) < 0)
			return (-1);
		free_pipex(&pipex, CMD_ARG);
		free_pipex(&pipex, CMD);
	}
	return (0);
}

void	pipex_process(char **argv, char **envp, t_pipex *pipex)
{
	pipex->i = -1;
	while (++(pipex->i) < pipex->nb_cmd)
	{
		if (process_child(argv, envp, *pipex) < 0)
		{
			free_pipex(pipex, ALL);
			msg_error("Error");
		}
	}
	close_fd(pipex);
	waitpid(-1, NULL, 0);
}
