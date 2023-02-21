/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:49:45 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/21 18:11:41 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"
#include <errno.h>

void	pipe_child(t_command_data *cmd, char **envp)
{
	int		ret;

	if (cmd->path == NULL)
		exit_child("command not found: ", cmd->cmd[0], 3);
	if (cmd->read_from < 0)
		write(STDIN_FILENO, "\0", 1);
	else
		dup2(cmd->read_from, STDIN_FILENO);
	dup2(cmd->write_to, STDOUT_FILENO);
	close(cmd->to_close);
	ret = execve(cmd->path, cmd->cmd, envp);
	if (ret == -1)
		exit_child("exeve failed: ", cmd->cmd[0], errno); //process failed
}

// void	baby(t_pipex *pipex)
// {
// 	char	*temp;
// 	char	path[1000];
// 	int		ret;

// 	dup2(pipex->p[0], 0);
// 	dup2(pipex->outfile_fd, 1);
// 	close(pipex->p[1]);
// 	temp = find_correct_path(pipex->cmd2[0], pipex->paths);
// 	if (!temp)
// 		exit_child("command not found: ", pipex->cmd2[0], 3);
// 	ft_strlcpy(path, temp, 1000);
// 	free (temp);
// 	ret = execve(path, pipex->cmd2, pipex->envp);
// 	if (ret == -1)
// 		exit_child("exeve failed: ", pipex->cmd2[0], errno);
// }

		// ft_putstr_fd(strerror(22), 2);
		// ft_putstr_fd("command not found: ", 2);
		// ft_putendl_fd(pipex->cmd1[0], 2);


// void	firstborn(t_pipex *pipex)
// {
// 	char	*temp;
// 	char	path[1000];
// 	int		ret;

// 	dup2(pipex->infile_fd, 0);
// 	dup2(pipex->p[1], 1);
// 	close(pipex->p[0]);
// 	temp = find_correct_path(pipex->cmd1[0], pipex->paths);
// 	if (!temp)
// 	{
// 		exit_child("command not found: ", pipex->cmd1[0], 3);
// 	}	
// 	ft_strlcpy(path, temp, 1000);
// 	free (temp);
// 	ret = execve(path, pipex->cmd1, pipex->envp);
// 	if (ret == -1)
// 		exit_child("exeve failed: ", pipex->cmd1[0], errno);
// }

// void	baby(t_pipex *pipex)
// {
// 	char	*temp;
// 	char	path[1000];
// 	int		ret;

// 	dup2(pipex->p[0], 0);
// 	dup2(pipex->outfile_fd, 1);
// 	close(pipex->p[1]);
// 	temp = find_correct_path(pipex->cmd2[0], pipex->paths);
// 	if (!temp)
// 		exit_child("command not found: ", pipex->cmd2[0], 3);
// 	ft_strlcpy(path, temp, 1000);
// 	free (temp);
// 	ret = execve(path, pipex->cmd2, pipex->envp);
// 	if (ret == -1)
// 		exit_child("exeve failed: ", pipex->cmd2[0], errno);
// }