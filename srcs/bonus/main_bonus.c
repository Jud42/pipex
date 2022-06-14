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

static int	parse_in(char **argv, t_pipex *pipex)
{
	int	ret;

	ret = 5;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		pipex->here_doc = 1;
		ret = 6;
	}
	else 
		pipex->here_doc = 0;
	return (ret);
}

static void	pipe_init(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (pipe(pipex->tube + (i * 2)) < 0)
		{
			free_pipex(pipex, ALL);
			msg_error("Error: pipe_init");
		}
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	
	if (argc < parse_in(argv, &pipex))
		return (0);
	init_pipex(&pipex, argc, argv);
	pipex.tube = (int *)malloc(sizeof(int) * pipex.nb_pipe);
	if (!pipex.tube)
	{
		free_pipex(&pipex, ALL);
		msg_error("Error: malloc");
	}
	pipe_init(&pipex);
	take_path(envp, &pipex); //all path exists
	pipex_process(argc, argv, envp, &pipex);
	free(pipex.tube);
	free_pipex(&pipex, ALL);
	return (0);
}
