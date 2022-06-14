/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:23:22 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/14 21:29:45 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msg_error(char	*s)
{
	perror(s);
	exit(1);
}
/*----------------------------------------*/

void	free_pipex(t_pipex *pipex, int flag)
{
	int	i;

	i = -1;	
	if (flag == ALL && pipex->path)
	{
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
		msg_error("Error: command not found");
}
/*-------------------------------------------------------------*/

void	take_path(char **envp, t_pipex *pipex) //take the all PATH from envp
{
	while (*envp++ && ft_strncmp(*envp, "PATH", 4) != 0)
		;
	while (*(*envp) && *(*envp) != '/') //similar to envp[i][++j]
		(*envp)++;
	pipex->path = ft_split((*envp), ':'); // (*envp) take the all char from index (*) stopped until EOF.
}
