/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:42 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/20 17:48:16 by jebouche         ###   ########.fr       */
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

void	setup_pipex(t_pipex *pipex, char **argv, char **envp)
{
	int	pipe_ret;

	pipe_ret = pipe(pipex->p);
	ft_bzero(pipex, sizeof(t_pipex));
	if (pipe_ret == -1)
		setup_exit("Pipe creation", 2);
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
		setup_exit(argv[1], 3);
	pipex->outfile_fd = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pipex->outfile_fd == -1)
		setup_exit(argv[4], 4);
	pipex->paths = get_paths(envp);
	pipex->cmd1 = get_args(argv[2]);
	pipex->cmd2 = get_args(argv[3]);
	if (!pipex->cmd1 || !pipex->cmd2)
		cleanup_pipex_parent(pipex, "Split", EINVAL);
	if (!pipex->paths)
		cleanup_pipex_parent(pipex, "Split", ENOMEM);
}

int	continue_parent(t_pipex *pipex, int pid)
{
	int	exit_status;
	int	pid2;

	exit_status = 0;
	waitpid(pid, &exit_status, 0);
	if (exit_status)
		cleanup_pipex_parent(pipex, "child failed", exit_status);
	else
	{
		pid2 = fork();
		if (pid2 == 0)
			baby(pipex);
		else
			waitpid(pid2, &exit_status, 0);
	}
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid;
	int		exit_status;

	exit_status = 0;
	if (argc == 5)
		setup_pipex(&pipex, argv, envp);
	else
	{
		ft_putendl_fd("Error: too few arguments", 2);
		exit(1);
	}
	pid = fork();
	if (pid < 0)
		cleanup_pipex_parent(&pipex, "error while forking", 3);
	if (pid == 0)
		firstborn(&pipex);
	else
	{
		exit_status = continue_parent(&pipex, pid);
	}
	cleanup_pipex_parent(&pipex, "Sucess", exit_status);
	return (0);
}
