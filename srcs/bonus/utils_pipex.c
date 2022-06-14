/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:23:22 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/14 11:59:09 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	msg_error(char	*s)
{
	perror(s);
	exit(1);
}
/*----------------------------------------*/

void	free_pipex(t_pipex *pipex, int flag)
{
	int	i;
	
	if (flag == ALL && pipex->path)
	{
		i = -1;
		while (pipex->path[++i])
			free(pipex->path[i]);
		free(pipex->path);
		pipex->path = NULL;
	}
	if (pipex->cmd_arg && (flag == CMD_ARG || flag == ALL))
	{
		i = -1;
		while (pipex->cmd_arg[++i])
			free(pipex->cmd_arg[i]);
		free(pipex->cmd_arg);
		pipex->cmd_arg = NULL;
	}
	if (pipex->cmd && (flag == CMD || flag == ALL))
	{
		free(pipex->cmd);
		pipex->cmd = NULL;
	}
}
/*-------------------------------*/

void	init_pipex(t_pipex	*pipex, int argc, char **argv)
{
	if (pipex->here_doc == 1)
		here_doc(argc, argv, pipex);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			msg_error("Error: infile");
		pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 00644);
		/*mode 00644 droit USR = 6/ GRP = 4/ OTH = 4
	 	4 = read/ 2 = write/ 1 = execute*/
		if (pipex->outfile < 0)
			msg_error("Error: outfile");
	}
	pipex->path = NULL;
	pipex->cmd = NULL;
	pipex->nb_cmd = argc - (3 + pipex->here_doc);
	pipex->nb_pipe = 2 * (pipex->nb_cmd - 1);
	pipex->cmd_arg = NULL;
}
/*--------------------------------------------------*/

void	take_path(char **envp, t_pipex *pipex) //take the all PATH from envp
{
	while (*envp++ && ft_strncmp(*envp, "PATH", 4) != 0)
		;
	while (*(*envp) && *(*envp) != '/') //similar to envp[i][++j]
		(*envp)++;
	pipex->path = ft_split((*envp), ':'); // (*envp) take the all char from index (*) stopped until EOF.
}
/*------------------------------------------------------*/

void	find_path(t_pipex *pipex)// take the **tab path & look for the good path
{
	int	i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (pipex->path[++i])
	{
		temp = ft_strjoin(pipex->path[i], "/");
		temp = ft_strjoin(temp, pipex->cmd_arg[0]);
		if (access(temp, X_OK) == 0)
		{
			pipex->cmd = temp;
			temp = NULL;
			break ;
		}
		free(temp);
	}
	if (!pipex->cmd)
	{
		//free_pipex(pipex, ALL);
		msg_error("Error");
	}
}
