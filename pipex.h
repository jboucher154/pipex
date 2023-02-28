/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:18 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/28 12:39:41 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// for strerror
# include <string.h>
// for access, dup2, execve, fork, pipe
# include <unistd.h>
// for exit
# include <stdlib.h>
// for waitpid, wait
# include <sys/wait.h>
// for error codes
# include <errno.h> 

# ifndef INFILE_ERROR
#  define INFILE_ERROR 4
# endif

# ifndef OUTFILE_ERROR
#  define OUTFILE_ERROR 5
# endif

# ifndef INPUT_ERROR
#  define INPUT_ERROR 1
# endif

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
char	**this_is_awkward(char *cmds);
void	exit_child(char *error_msg, char *arg, int exit_code);
void	cleanup_pipex_parent(t_pipex *pipex, int exit_code);
void	setup_error(char *error_msg, int exit_code, t_pipex *pipex);
void	free_array(char **to_free);
void	close_pipes(int pipe_in, int pipe_out);
void	pipe_child(t_command_data *cmd, char **envp);

#endif
