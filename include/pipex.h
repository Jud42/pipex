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
#include <sys/wait.h>
typedef struct s_pipex{
	char	**path;
	char	**cmd_arg;
	char	*cmd;
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
	int		tube[2];
} t_pipex;

void	msg_error(char *s);
void	init_pipex(t_pipex *pipex, char **argv);
void	free_pipex(t_pipex *pipex);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char 	**ft_split(const char *s, char sep);
char 	*ft_strjoin(char *s1, char *s2);
void	find_path(char	**envp, t_pipex *pipex);
void	pipex_process(char **argv, char	**envp, t_pipex *pipex);

#endif
