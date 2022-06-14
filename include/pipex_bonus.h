/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:15:59 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/03 17:14:26 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
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
	int	nb_cmd;
	int	nb_pipe;
	int	i;
	int	infile;
	int	outfile;
	int	here_doc;

	int	*tube;
} t_pipex;

void	msg_error(char *s);
void	here_doc(int argc, char **argv, t_pipex *pipex);
//int	ft_strlen(const char *s);
void	init_pipex(t_pipex *pipex, int argc, char **argv);
void	free_pipex(t_pipex *pipex, int flag);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char 	**ft_split(const char *s, char sep);
//char 	*ft_strjoin(char *s1, char *s2);
void	take_path(char **envp, t_pipex *pipex);
void	find_path(t_pipex *pipex);
void	pipex_process(int argc, char **argv, char	**envp, t_pipex *pipex);

#endif
