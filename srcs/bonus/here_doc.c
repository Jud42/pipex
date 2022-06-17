/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:17:25 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/17 16:32:18 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	file_in_out(char *argv, char *path, t_pipex *pipex)
{
	pipex->infile = open(path, O_RDONLY);
	if (pipex->infile < 0)
	{	
		unlink(path);
		msg_error("Error: infile");
	}
	pipex->outfile = open(argv, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (pipex->outfile < 0)
		msg_error("Error: outfile");
}

void	here_doc(int argc, char **argv, t_pipex *pipex)
{
	int		file_temp;
	char	*limiter;
	char	*temp;

	file_temp = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (file_temp < 0)
		msg_error("Error: file_temp_here_doc");
	pipex->here_doc = 1;
	temp = NULL;
	limiter = argv[2];
	while (1)
	{
		write(1, "heredoc> ", 9);
		temp = get_next_line(0);
		if (!temp)
			exit(1);
		if (!ft_strncmp(limiter, temp, ft_strlen(limiter)))
			break ;
		write(file_temp, temp, ft_strlen(temp));
		write(file_temp, "\n", 1);
		free(temp);
	}
	free(temp);
	close(file_temp);
	file_in_out(argv[argc - 1], ".heredoc", pipex);
}
