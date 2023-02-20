/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:49:01 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/20 17:24:06 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "libft.h"

void	free_array(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	cleanup_pipex_child(t_pipex *pipex, char *error_msg, int exit_code)
{
	if (exit_code)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(error_msg, 2);
	}
	// if (pipex->cmd1)
	// 	free_array(pipex->cmd1);
	// if (pipex->cmd2)
	// 	free_array(pipex->cmd2);
	// if (pipex->paths)
	// 	free_array(pipex->paths);
	close(pipex->infile_fd);
	// close(pipex->outfile_fd);
	exit(exit_code);
}

void	cleanup_pipex_parent(t_pipex *pipex, char *error_msg, int exit_code)
{
	if (exit_code)
	{
		perror(error_msg);
		// ft_printf("ERROR: %s", strerror(exit_code));
	}
	if (pipex->cmd1)
		free_array(pipex->cmd1);
	if (pipex->cmd2)
		free_array(pipex->cmd2);
	if (pipex->paths)
		free_array(pipex->paths);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	close(pipex->p[1]);
	close(pipex->p[0]);
	error_msg = NULL;
	exit(0);
}

void	setup_exit(char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}
