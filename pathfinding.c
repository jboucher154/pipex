/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:24:45 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/21 15:49:59 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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
	if (slash_fname)
		free(slash_fname);
	return (NULL);
}