/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:18 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/23 17:24:44 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> // for perror
# include <string.h> // for strerror
# include <unistd.h> // for access, dup, dup2, execve, fork, pipe, read, write, unlink?
# include <stdlib.h> // for exit
# include <sys/wait.h> // for waitpid, wait

typedef struct s_command_data
{
	char	**cmd;
	char	*path;
	int		read_from;
	int		write_to;
	int		to_close;

}			t_command_data;

typedef struct s_pipex
{
	struct s_command_data	*cmd_1;
	struct s_command_data	*cmd_2;
	int						p[2];
}				t_pipex;

char	*find_correct_path(char *fname, char **paths);
char	**get_paths(char **envp);

void	exit_child(char *error_msg, char *arg, int exit_code);
void	cleanup_pipex_parent(t_pipex *pipex, int exit_code);
void	exit_setup(char *error_msg, char *error_msg1, int exit_code);
void	free_array(char **to_free);
void	close_pipes(int pipe_in, int pipe_out);

void	pipe_child(t_command_data *cmd, char **envp);

#endif
