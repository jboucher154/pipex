#include "ft_printf.h"
#include "libft.h"
#include "pipex.h"
#include <fcntl.h>

// void	free_array(char **to_free)
// {
// 	int	i;

// 	i = 0;
// 	while (to_free[i])
// 	{
// 		free(to_free[i]);
// 		i++;
// 	}
// 	free(to_free);
// }

// void	cleanup_pipex(t_pipex *pipex, char *error_msg, int exit_code)
// {
// 	if (pipex->cmd1)
// 		free_array(pipex->cmd1);
// 	if (pipex->cmd2)
// 		free_array(pipex->cmd2);
// 	if (pipex->paths)
// 		free_array(pipex->paths);
// 	close(pipex->infile_fd);
// 	close(pipex->outfile_fd);
// 	perror(error_msg);
// 	exit(exit_code);
// }

// void	firstborn(t_pipex *pipex)
// {
// 	char	*temp;
// 	char 	path[1000];

// 	dup2(pipex->infile_fd, 0); //reroute infile contents to stdin
// 	dup2(pipex->p[1], 1); //reroute stdout to pipe
// 	close(pipex->p[0]); //close read end of pipe
// 	temp = find_correct_path(pipex->cmd1[0], pipex->paths);
// 	if (!temp)
// 		cleanup_pipex(pipex, "Firstborn", 5);
// 	ft_strlcpy(path, temp, 1000);
// 	free (temp);
// 	execve(path, pipex->cmd1, pipex->envp);
// }

// void	sibling(t_pipex *pipex)
// {
// 	char	*temp;
// 	char 	path[1000];

// 	dup2(pipex->p[0], 0); //reroute pipe contents to stdin
// 	dup2(pipex->outfile_fd, 1); //reroute stdout to outfile
// 	close(pipex->p[1]); //close write end of pipe
// 	temp = find_correct_path(pipex->cmd2[0], pipex->paths);
// 	if (!temp)
// 		cleanup_pipex(pipex, "Sibling", 6);
// 	ft_strlcpy(path, temp, 1000);
// 	free (temp);
// 	execve(path, pipex->cmd2, pipex->envp);
// }

// void	setup_pipex(t_pipex *pipex, char **argv, char **envp)
// {
// 		int pipe_ret = pipe(pipex->p); //create pipe
// 		if (pipe_ret == -1)
// 		{
// 			perror("Pipe");
// 			exit(2);
// 		}
// 		pipex->infile_fd = open(argv[1], O_RDONLY);
// 		if (pipex->infile_fd == -1)
// 		{
// 			perror("Infile");
// 			exit(1);
// 		}
// 		pipex->outfile_fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
// 		if (pipex->outfile_fd == -1)
// 		{
// 			perror("Outfile");
// 			exit(3);
// 		}
// 		pipex->paths = get_paths(envp);
// 		pipex->cmd1 = ft_split(argv[2], ' ');
// 		pipex->cmd2 = ft_split(argv[3], ' ');
// 		if (!pipex->cmd1 || !pipex->cmd2 || !pipex->paths)
// 		{
// 			cleanup_pipex(pipex);
// 			perror("Split");
// 			exit(4);
// 		}
// }

// void	run_test(int argc, char **argv, char **envp)
// {
// 	t_pipex	pipex;

// 	if (argc == 5)
// 		setup_pipex(&pipex, argv, envp);
// 	else
// 		exit(1);
// 		int pid = fork();
// 		if (pid == 0)
// 			firstborn(&pipex);
// 		else
// 			wait(NULL); //wait for child to finish
// 		int pid2 = fork();
// 		if (pid2 == 0)
// 		{
// 			sibling(&pipex);
// 		}
// 		else
// 		{
// 			close(pipex.p[1]); //close write end of pipe
// 			wait(NULL); //wait for child to finish
// 		}
// 	// char *line;
// 	// while ((line = get_next_line(pipex.p[0])))
// 	// {
// 	// 	ft_printf("%s", line);
// 	// 	free(line);
// 	// }
// 	close(pipex.p[0]);
// 	cleanup_pipex(&pipex);
// }

		// int pipe_ret = pipe(pipex.p); //create pipe
		// if (pipe_ret == -1)
		// {
		// 	perror("Pipe");
		// 	exit(1);
		// }
		// pipex.infile_fd = open(argv[1], O_RDONLY);
		// if (pipex.infile_fd == -1)
		// {
		// 	perror("Infile");
		// 	exit(1);
		// }
		// pipex.outfile_fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
		// if (pipex.outfile_fd == -1)
		// {
		// 	perror("Outfile");
		// 	exit(2);
		// }
		// pipex.paths = get_paths(envp);
		// pipex.cmd1 = ft_split(argv[2], ' ');
		// pipex.cmd2 = ft_split(argv[3], ' ');




// char	**get_paths(char **envp)
// {
// 	int		i;
// 	char	**paths;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 			paths = ft_split(envp[i] + 5, ':');
// 		i++;
// 	}
// 	return (paths);
// }

// char	*find_correct_path(char *fname, char **paths)
// {
// 	int		i;
// 	char	*path;
// 	char	*slash_fname;

// 	i  = 0;
// 	slash_fname = ft_strjoin("/", fname);
// 	while (paths[i] && slash_fname)
// 	{
// 		path = ft_strjoin(paths[i], slash_fname);
// 		if (path)
// 		{
// 			if (access(path, X_OK) == 0)
// 			{
// 				free(slash_fname);
// 				return (path);
// 			}
// 			else
// 				free(path);
// 		}
// 		i++;
// 	}
// 	free(slash_fname);
// 	return (NULL);
// }