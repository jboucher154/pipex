/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:49:45 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/23 14:10:34 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"
#include <errno.h>

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
		exit_child("command not found: ", cmd->cmd[0], 3);
	else if (cmd->read_from < 0)
		exit(1);
	ret = execve(cmd->path, cmd->cmd, envp);
	if (ret == -1)
		exit_child("exeve failed: ", cmd->cmd[0], errno);
}
