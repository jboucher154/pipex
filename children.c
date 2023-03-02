/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:49:45 by jebouche          #+#    #+#             */
/*   Updated: 2023/03/02 14:34:05 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*bail_on_child is called by the child process if the command is not found.
 * It will exit with an error code.
 */
static void	bail_on_child(t_command_data *cmd)
{
	if (cmd->cmd == NULL)
		exit_child("command not found: ", " ", CMD_ERROR);
	else
		exit_child("command not found: ", cmd->cmd[0], CMD_ERROR);
}

/* pipe_child is called by child processes. It will dup2 the read and write
 * file descriptors to the correct file descriptors, close the file descriptors
 * that are not needed, and then execve the command. If the command is not
 * found, it will exit with an error code.
 */
void	pipe_child(t_command_data *cmd, char **envp)
{
	int		ret;

	if (cmd->read_from < 0)
		write(STDIN_FILENO, "\0", 1);
	else
	{
		dup2(cmd->read_from, STDIN_FILENO);
		close(cmd->read_from);
	}
	dup2(cmd->write_to, STDOUT_FILENO);
	close(cmd->write_to);
	close(cmd->to_close);
	if (cmd->path == NULL)
		bail_on_child(cmd);
	else if (cmd->read_from < 0)
		exit(1);
	ret = execve(cmd->path, cmd->cmd, envp);
	if (ret == -1)
		exit_child("exeve failed: ", cmd->cmd[0], errno);
}
