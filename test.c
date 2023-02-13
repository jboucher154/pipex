#include "ft_printf.h"
#include "libft.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(envp[i] + 5, ':');
		i++;
	}
	return (paths);
}

char	*find_correct_path(char *fname, char **paths)
{
	int		i;
	char	*path;
	char	*slash_fname;

	i  = 0;
	slash_fname = ft_strjoin("/", fname);
	while (paths[i] && slash_fname)
	{
		path = ft_strjoin(paths[i], slash_fname);
		if (path)
		{
			if (access(path, X_OK) == 0)
			{
				free(slash_fname);
				return (path);
			}
			else
				free(path);
		}
		i++;
	}
	free(slash_fname);
	return (NULL);
}

void	run_test(int argc, char **argv, char **envp)
{
	char	**paths;
	char	*path;
	char	*args[] = {"ls", "-l", NULL};

	if (argc)
	{
		argv = 0;
		paths = get_paths(envp);
		// for (int i = 0; paths[i]; i++)
		// 	ft_printf("%s\n", paths[i]);
		path = find_correct_path("ls", paths);
		// ft_printf("RIGHT PATH: %s\n", path);
		execve(path, args, envp);
	}
}
