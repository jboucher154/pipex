/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:42 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/15 12:53:26 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h> // for open
#include "libft.h"
#include "ft_printf.h"

char	**get_args(char *commands)
{
	char	**args;

	if (ft_strchr(commands, '\''))
	{
		args = ft_split(commands, '\'');
		if (args)
		{
			args[0] = ft_strtrim(args[0], " "); // will leave memory leak?
		}
		for (int i = 0; args[i]; i++)
			ft_printf("args[%d]: %s\n", i, args[i]);
	}
	else if (ft_strchr(commands, '\"'))
		args = ft_split(commands, '\"');
	else
		args = ft_split(commands, ' ');
	return (args);
}

void	setup_pipex(t_pipex *pipex, char **argv, char **envp)
{
	ft_bzero(pipex, sizeof(t_pipex));
	int pipe_ret = pipe(pipex->p); //create pipe
	if (pipe_ret == -1)
	{
		perror("Pipe");
		exit(2);
	}
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror("Infile");
		exit(1);
	}
	pipex->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		perror("Outfile");
		exit(3);
	}
	pipex->paths = get_paths(envp);
	pipex->cmd1 = get_args(argv[2]);
	pipex->cmd2 = get_args(argv[3]);
	// pipex->cmd1 = ft_split(argv[2], ' ');
	// pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd1 || !pipex->cmd2 || !pipex->paths)
		cleanup_pipex(pipex, "Split", 4);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid;
	int		pid2;

	if (argc == 5)
		setup_pipex(&pipex, argv, envp);
	else
		exit(1);
	pid = fork();
	if (pid == 0)
		firstborn(&pipex);
	else
	{
		wait(NULL); //wait for child to finish
		pid2 = fork();
		if (pid2 == 0)
			baby(&pipex);
		else
		{
			close(pipex.p[1]); //close write end of pipe
			wait(NULL); //wait for child to finish
		}
	}
	close(pipex.p[0]);
	cleanup_pipex(&pipex, "Sucess", 0);
	return (0);
}
	// run_test(argc, argv, envp);