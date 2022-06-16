/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:15:59 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/16 19:36:09 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include "get_next_line.h"
# define CMD 1
# define CMD_ARG 2
# define ALL 3

typedef struct s_pipex{
	char	**path;
	char	**cmd_arg;
	char	*cmd;
	pid_t	pid;
	int		fd[2];
	int		infile;
	int		outfile;
}	t_pipex;

int		error_cmd(char *s);
void	msg_error(char *s);
void	free_pipex(t_pipex *pipex, int flag);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *s, char sep);
void	take_path(char **envp, t_pipex *pipex);
void	find_path(t_pipex *pipex);

#endif
