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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	
	if (argc != 5)
		return (0);
	init_pipex(&pipex, argv);
	pipex_process(argv, envp, &pipex);
	free_pipex(&pipex);
	return (0);
}
