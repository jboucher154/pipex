/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:42 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/23 17:51:13 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h> // for open
#include "libft.h"
#include "ft_printf.h"
#include <errno.h>

char	**this_is_awkward(char *commands)
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

char	**get_args(char *commands)
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

void	setup_commands(t_pipex *pipex, char **paths)
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

void	setup_pipex(t_pipex *pipex, char **argv, char **envp)
{
	int		pipe_ret;
	char	**paths;

	pipex->cmd_1 = ft_calloc(1, sizeof(t_command_data));
	pipex->cmd_2 = ft_calloc(1, sizeof(t_command_data));
	if (!pipex->cmd_1 || !pipex->cmd_2)
		cleanup_pipex_parent(pipex, ENOMEM);
	pipe_ret = pipe(pipex->p);
	if (pipe_ret == -1)
		exit_setup("error", "pipe creation failed", EPIPE);
	pipex->cmd_1->read_from = open(argv[1], O_RDONLY);
	if (pipex->cmd_1->read_from == -1)
		exit_setup("no such file or directory: ", argv[1], 0);
	pipex->cmd_2->write_to = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pipex->cmd_2->write_to == -1)
		exit_setup("no such file or directory: ", argv[4], 4);
	paths = get_paths(envp);
	pipex->cmd_1->cmd = get_args(argv[2]);
	pipex->cmd_2->cmd = get_args(argv[3]);
	if (!pipex->cmd_1->cmd || !pipex->cmd_2->cmd)
		cleanup_pipex_parent(pipex, EINVAL); // invalid argument
	if (!paths)
		cleanup_pipex_parent(pipex, ENOMEM);
	setup_commands(pipex, paths);
	free_array(paths);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid;
	int		pid2;

	if (argc < 5 || argc > 5)
		exit_setup(NULL, "invalid number of arguments", 1);
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
