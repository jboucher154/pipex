/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:24:45 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/24 15:01:31 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

/*get_paths takes in the environment variable array and returns an array of 
 *paths from the PATHS variable in the environment
 */
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

/*find_correct_path takes in a program name and an array of paths from the 
 *environment and returns the path to the program if it exists in 
 *one of the paths, if it doesn't exist it will return NULL
 */
char	*find_correct_path(char *fname, char **paths)
{
	int		i;
	char	*path;
	char	*slash_fname;

	i = 0;
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
	if (slash_fname)
		free(slash_fname);
	return (NULL);
}
