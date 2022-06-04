/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:23:22 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/03 18:18:22 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	msg_error(char	*s)
{
	perror(s);
	exit(1);
}
/*-------------------------------*/

void	init_pipex(t_pipex	*pipex, char **argv)
{
	pipex->path = NULL;
	pipex->cmd = NULL;
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		msg_error("Error: infile");
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 00644);
	/*mode 00644 droit USR = 6/ GRP = 4/ OTH = 4
	 4 = read/ 2 = write/ 1 = execute*/
	if (pipex->outfile < 0)
		msg_error("Error: outfile");
	pipex->cmd_arg = NULL;
}
/*----------------------------------------*/

void	free_pipex(t_pipex *pipex)
{
	if (pipex->path)
		free(pipex->path);
	if (pipex->cmd_arg)
		free(pipex->cmd_arg);
	if (pipex->cmd)
		free(pipex->cmd);
}
/*--------------------------------------------------*/

static void	take_path(char **envp, t_pipex *pipex) //take the all PATH from envp
{
	while (*envp++ && ft_strncmp(*envp, "PATH", 4) != 0)
		;
	while (*(*envp) && *(*envp) != '/') //similar to envp[i][++j]
		(*envp)++;
	pipex->path = ft_split((*envp), ':'); // (*envp) take the all char from index (*) stopped until EOF.
}
/*------------------------------------------------------*/

void	find_path(char **envp, t_pipex *pipex)// take the **tab path & look for the good path
{
	int	i;
	char	*temp;

	i = -1;
	temp = NULL;
	take_path(envp, pipex);
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
		free_pipex(pipex);
		msg_error("Error: Command not found");
	}
}
