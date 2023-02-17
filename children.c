/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:49:45 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/17 16:44:53 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"

void	firstborn(t_pipex *pipex)
{
	char	*temp;
	char 	path[1000];

	dup2(pipex->infile_fd, 0); //reroute infile contents to stdin
	dup2(pipex->p[1], 1); //reroute stdout to pipe
	close(pipex->p[0]); //close read end of pipe
	temp = find_correct_path(pipex->cmd1[0], pipex->paths);
	if (!temp)
	{
		// ft_putstr_fd(strerror(22), 2);
		// ft_putstr_fd("command not found: ", 2);
		// ft_putendl_fd(pipex->cmd1[0], 2);
		cleanup_pipex_child(pipex, pipex->cmd1[0], 3);
	}	
	ft_strlcpy(path, temp, 1000);
	free (temp);
	execve(path, pipex->cmd1, pipex->envp);
	//handle errors for execve?
}

void	baby(t_pipex *pipex)
{
	char	*temp;
	char 	path[1000];

	dup2(pipex->p[0], 0); //reroute pipe contents to stdin
	dup2(pipex->outfile_fd, 1); //reroute stdout to outfile
	close(pipex->p[1]); //close write end of pipe
	temp = find_correct_path(pipex->cmd2[0], pipex->paths);
	if (!temp)
		cleanup_pipex_child(pipex, pipex->cmd2[0], 6);
	ft_strlcpy(path, temp, 1000);
	free (temp);
	execve(path, pipex->cmd2, pipex->envp);
}