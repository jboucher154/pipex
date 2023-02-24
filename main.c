/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:42 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/24 15:12:02 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include "libft.h"

/* this_is_awkward is the function that handles the single quotes in the 
 * commands. It takes the commands as a string argument and splits the commands
 * into	an array of arguments, then copies them into malloced arrays. It assumes 
 * that there are only two arguments
 */
static char	**this_is_awkward(char *commands)
{
	char	**awk_args;
	char	**args;

	awk_args = (char **)malloc(sizeof(char *) * 3);
	args = ft_split(commands, '\'');
	if (awk_args && args && args[0] && args[1])
	{
		awk_args[2] = NULL;
		awk_args[0] = ft_strtrim(args[0], " ");
		awk_args[1] = ft_strdup(args[1]);
	}
	free_array(args);
	return (awk_args);
}

/* get_args is the function that gets the arguments for the commands. It takes
 * the commands as a string argument. It then checks if there are any single 
 * quotes in the commands. If there are, it calls the this_is_awkward function 
 * handle the single quotes. If there are no single quotes, it calls the
 * to ft_split function to split the commands into an array of arguments.
 */
static char	**get_args(char *commands)
{
	char	**args;

	if (commands[0] == '\0')
		return (NULL);
	if (ft_strchr(commands, '\''))
		args = this_is_awkward(commands);
	else
		args = ft_split(commands, ' ');
	return (args);
}

/* setup_commands is the function that sets up the commands in the pipex struct.
 * It takes the pipex struct and the paths array as arguments. It then finds
 * the correct paths for the commands and the correct read and write file
 * descriptors for the commands. It also sets up the correct file descriptors
 * to close for the commands.
 */
static void	setup_commands(t_pipex *pipex, char **paths)
{
	if (pipex->cmd_1->cmd != NULL)
		pipex->cmd_1->path = find_correct_path(pipex->cmd_1->cmd[0], paths);
	pipex->cmd_1->write_to = pipex->p[1];
	pipex->cmd_1->to_close = pipex->p[0];
	if (pipex->cmd_2->cmd != NULL)
		pipex->cmd_2->path = find_correct_path(pipex->cmd_2->cmd[0], paths);
	if (pipex->cmd_1->cmd == NULL)
		pipex->cmd_2->read_from = pipex->cmd_1->read_from;
	else
		pipex->cmd_2->read_from = pipex->p[0];
	pipex->cmd_2->to_close = pipex->p[1];
}

/* setup_pipex is the function that sets up the pipex struct. It takes the
 * arguments from the command line and the environment variables as arguments.
 * It then sets up the pipex struct with the correct values for the commands
 * and the pipes. It also opens the files and checks for errors. 
 */
static void	setup_pipex(t_pipex *pipex, char **argv, char **envp)
{
	int		pipe_ret;
	char	**paths;

	pipex->cmd_1 = ft_calloc(1, sizeof(t_command_data));
	pipex->cmd_2 = ft_calloc(1, sizeof(t_command_data));
	if (!pipex->cmd_1 || !pipex->cmd_2)
		cleanup_pipex_parent(pipex, ENOMEM);
	pipe_ret = pipe(pipex->p);
	if (pipe_ret == -1)
		setup_error("Pipe creation failed", EPIPE, pipex);
	pipex->cmd_1->read_from = open(argv[1], O_RDONLY);
	if (pipex->cmd_1->read_from == -1)
		setup_error(argv[1], INFILE_ERROR, pipex);
	pipex->cmd_2->write_to = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pipex->cmd_2->write_to == -1)
		setup_error(argv[4], OUTFILE_ERROR, pipex);
	paths = get_paths(envp);
	pipex->cmd_1->cmd = get_args(argv[2]);
	pipex->cmd_2->cmd = get_args(argv[3]);
	setup_commands(pipex, paths);
	free_array(paths);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid;
	int		pid2;

	if (argc < 5 || argc > 5)
		setup_error("Input error: Enter 4 arguments", INPUT_ERROR, &pipex);
	setup_pipex(&pipex, argv, envp);
	pid2 = 0;
	pid = fork();
	if (pid == 0)
		pipe_child(pipex.cmd_1, envp);
	else
	{
		pid2 = fork();
		if (pid2 == 0)
			pipe_child(pipex.cmd_2, envp);
		else
			close_pipes(pipex.p[0], pipex.p[1]);
	}
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	cleanup_pipex_parent(&pipex, 0);
	return (0);
}
