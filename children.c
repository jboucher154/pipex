/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:49:45 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/15 12:51:48 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	firstborn(t_pipex *pipex)
{
	char	*temp;
	char 	path[1000];

	dup2(pipex->infile_fd, 0); //reroute infile contents to stdin
	dup2(pipex->p[1], 1); //reroute stdout to pipe
	close(pipex->p[0]); //close read end of pipe
	temp = find_correct_path(pipex->cmd1[0], pipex->paths);
	if (!temp)
		cleanup_pipex(pipex, "Firstborn", 5);
	ft_strlcpy(path, temp, 1000);
	free (temp);
	execve(path, pipex->cmd1, pipex->envp);
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
		cleanup_pipex(pipex, "Sibling", 6);
	ft_strlcpy(path, temp, 1000);
	free (temp);
	execve(path, pipex->cmd2, pipex->envp);
}