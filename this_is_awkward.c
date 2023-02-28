/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   this_is_awkward.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:38:07 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/28 14:38:08 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

/* count_args takes in a string of commands and returns the number of
 * arguments in the string of commands (separated by spaces or single quotes)
 */
static int	count_args(char *cmds)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (cmds[i])
	{
		if (cmds[i] == ' ')
		{
			count++;
			if (cmds[i] && cmds[i + 1] == '\'')
				i++;
		}
		if (cmds[i] == '\'')
		{
			i++;
			while (cmds[i] != '\'')
				i++;
		}
		i++;
	}
	return (count);
}

/* find_start takes in a string of commands and an index and returns the
 * index of the start of the next word from the index
 */
static int	find_start(char *cmds, int index)
{
	while (index != 0 && cmds[index] != '\0')
	{
		if (cmds[index] == ' ' || cmds[index] == '\0')
		{
			index++;
			if (cmds[index] && cmds[index] == '\'')
				index++;
			break ;
		}
		else if (cmds[index] == '\'')
		{
			if (cmds[index - 1] && cmds[index - 1] == ' ')
			{
				index++;
				break ;
			}
		}
		index++;
	}
	return (index);
}

/* find_word takes in a string of commands, an index, and an array of two
 * integers. It finds the start and end of the word at the index and stores
 * the start and end in the array.
 */
void	find_word(char *cmds, int index, int *start_end)
{
	index = find_start(cmds, index);
	start_end[0] = index;
	if (cmds[index] && index != 0 && cmds[index - 1] == '\'')
	{
		while (cmds[index] && cmds[index] != '\'')
			index++;
	}
	else
	{
		while (cmds[index] && cmds[index] != ' ')
		{
			index++;
		}
	}
	start_end[1] = index;
}

/* fill_args takes in a string of commands, an array of arguments, and the
 * number of arguments. It assigns the wordds found by find_word to the 
 * array of arguments using ft_substr.
 */
void	fill_args(char *cmds, char **args, int arg_count)
{
	int		i;
	int		k;
	int		start_end[2];

	start_end[0] = 0;
	start_end[1] = 0;
	i = 0;
	k = 0;
	while (i < arg_count)
	{
		find_word(cmds, k, start_end);
		args[i] = ft_substr(cmds, start_end[0], start_end[1] - start_end[0]);
		if (!args[i])
		{
			free_array(args);
			args = NULL;
			break ;
		}
		k = start_end[1];
		i++;
	}
}

/* this_is_awkward handles commands with single quotes in the It takes the 
 * commands as a string argument and splits the commands into an array of
 * arguments that can be passed to execve.
 */
char	**this_is_awkward(char *cmds)
{
	char	**awk_args;
	int		arg_count;

	arg_count = count_args(cmds);
	awk_args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!awk_args)
		return (NULL);
	awk_args[arg_count] = NULL;
	fill_args(cmds, awk_args, arg_count);
	return (awk_args);
}
