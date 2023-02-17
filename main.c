/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:42 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/17 16:56:29 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h> // for open
#include "libft.h"
#include "ft_printf.h"
#include <errno.h>

char **this_is_awkward(char *commands)
{
	char **awk_args;
	char **args;

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
	ft_bzero(pipex, sizeof(t_pipex));
	int pipe_ret = pipe(pipex->p);
	if (pipe_ret == -1)
	{
		perror("Pipe creation");
		exit(2);
	}
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror(argv[1]);
		exit(3);
	}
	pipex->outfile_fd = open(argv[4],  O_TRUNC | O_CREAT | O_WRONLY , 0644);
	if (pipex->outfile_fd == -1)
	{
		perror(argv[4]);
		exit(4);
	}
	pipex->paths = get_paths(envp);
	pipex->cmd1 = get_args(argv[2]);
	pipex->cmd2 = get_args(argv[3]);
	if (!pipex->cmd1 || !pipex->cmd2)
		cleanup_pipex_parent(pipex, "Split", EINVAL);
	if (!pipex->paths)
		cleanup_pipex_parent(pipex, "Split", ENOMEM);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid;
	int		pid2;
	int		exit_status;

	int fd = open("/dev/urandom", O_RDONLY);
	ft_printf("OPEN res: %i", fd);
	exit_status = 0;
	if (argc == 5) //argc == 5
		setup_pipex(&pipex, argv, envp);
	else
		exit(1); //5 is input output error
	pid = fork();
	if (pid == 0)
		firstborn(&pipex);
	else
	{
		waitpid(pid, &exit_status, 0); //wait for child to finish
		if (exit_status)
			cleanup_pipex_parent(&pipex, "Wait", exit_status);
		else
		{
			pid2 = fork();
			if (pid2 == 0)
				baby(&pipex);
			else
			{
				close(pipex.p[1]); //close write end of pipe
				waitpid(pid2, &exit_status, 0); //wait for child to finish
			}
		}
	}
	close(pipex.p[0]);
	cleanup_pipex_parent(&pipex, "Sucess", 0);
	return (0);
}
