/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:18 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/20 17:40:11 by jebouche         ###   ########.fr       */
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
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	**paths;
	int		infile_fd;
	int		outfile_fd;
	int		p[2];
}			t_pipex;

char	*find_correct_path(char *fname, char **paths);
char	**get_paths(char **envp);

void	setup_exit(char *msg, int exit_code);
void	cleanup_pipex_child(t_pipex *pipex, char *error_msg, int exit_code);
void	cleanup_pipex_parent(t_pipex *pipex, char *error_msg, int exit_code);
void	free_array(char **to_free);

void	firstborn(t_pipex *pipex);
void	baby(t_pipex *pipex);

//for testing
int		run_test(int argc, char **argv, char **envp);

#endif
