/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:49:01 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/21 16:32:15 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "libft.h"
#include <errno.h>

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

void	exit_child(char *error_msg, char *arg, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putendl_fd(arg, 2);
	exit(exit_code);
}

void	cleanup_pipex_parent(t_pipex *pipex, int exit_code)
{
	char	*msg;

	msg = NULL;
	if (exit_code == EINVAL || exit_code == ENOMEM)
	{
		msg = strerror(exit_code);
		ft_putstr_fd("pipex: ", 2);
		ft_putendl_fd(msg, 2);
	}
	if (pipex->cmd1)
		free_array(pipex->cmd1);
	if (pipex->cmd2)
		free_array(pipex->cmd2);
	if (pipex->paths)
		free_array(pipex->paths);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	close(pipex->p[0]);
	close(pipex->p[1]);
	exit(exit_code);
}

void	exit_setup(char *error_msg, char *error_msg1, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	ft_putendl_fd(error_msg1, 2);
	exit(exit_code);
}
