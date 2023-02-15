/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:18 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/15 12:51:55 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> // for perror
# include <string.h> // for strerror
# include <unistd.h> // for access, dup, dup2, execve, fork, pipe, read, write, unlink?
# include <stdlib.h> // for exit
# include <sys/wait.h> // for waitpid, wait

typedef struct s_pipex
{
	char	**cmd1; //array of commands, use [0] to find correct path
	char	**cmd2;
	char	**envp;
	char	**paths; //array of paths, use to find correct one for cmd1 and cmd2
	int		infile_fd;
	int		outfile_fd;
	int		p[2]; //pipe
}			t_pipex;

char	*find_correct_path(char *fname, char **paths);
char	**get_paths(char **envp);

void	cleanup_pipex(t_pipex *pipex, char *error_msg, int exit_code);

void	firstborn(t_pipex *pipex);
void	baby(t_pipex *pipex);

//for testing
// void	run_test(int argc, char **argv, char **envp);

#endif
