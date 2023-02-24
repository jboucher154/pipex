/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:49:01 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/24 15:18:32 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

/* free_array takes in a double pointer to a char array and frees the memory
 */
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

/* exit_child takes in an error message, an argument, and an exit code and
 * prints the error message and the argument to stderr, then exits with the
 * exit code
 */
void	exit_child(char *error_msg, char *arg, int exit_code)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
	exit(exit_code);
}

/* cleanup_pipex_parent takes in a pointer to a pipex struct and an exit code
 * and frees the memory allocated to the pipex struct, closes the pipes
 * and exits with the exit code
 */
void	cleanup_pipex_parent(t_pipex *pipex, int exit_code)
{
	if (exit_code == INPUT_ERROR)
		exit(exit_code);
	if (pipex->cmd_1->cmd)
		free_array(pipex->cmd_1->cmd);
	if (pipex->cmd_1->path)
		free(pipex->cmd_1->path);
	if (pipex->cmd_2->cmd)
		free_array(pipex->cmd_2->cmd);
	if (pipex->cmd_2->path)
		free(pipex->cmd_2->path);
	if (pipex->cmd_1)
		free(pipex->cmd_1);
	if (pipex->cmd_2)
		free(pipex->cmd_2);
	close_pipes(pipex->cmd_1->read_from, pipex->cmd_2->write_to);
	close_pipes(pipex->p[0], pipex->p[1]);
	exit(exit_code);
}

/* close_pipes takes in two file descriptors and closes them
 */
void	close_pipes(int pipe_in, int pipe_out)
{
	close(pipe_in);
	close(pipe_out);
}

/* setup_error takes in an error message, an exit code, and a pointer to a
 * pipex struct and prints the error message to stderr. It only exits with the
 * exit code if the error is an input, outfile, or epipe error
 */
void	setup_error(char *error_msg, int exit_code, t_pipex *pipex)
{
	char	*msg;

	msg = strerror(errno);
	if (exit_code == INFILE_ERROR || exit_code == OUTFILE_ERROR)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(error_msg, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putendl_fd(error_msg, STDERR_FILENO);
	}
	if (exit_code == INPUT_ERROR || exit_code == OUTFILE_ERROR || \
		exit_code == EPIPE)
		cleanup_pipex_parent(pipex, exit_code);
}
