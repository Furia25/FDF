/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_managing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:57:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/07 16:59:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int try_open_file(int *fd, char *file_path)
{
	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
		return (0);
	return (1);
}

int	check_file(int fd)
{
	if (fd == -1)
		return (0);
	return (1);
}

void	free_chartab(char **tab)
{
	size_t	index;

	index = 0;
	while (tab[index])
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}

static int *parse_line(char *line)
{
	char 	**words;
	int		*result;
	size_t	index;

	if (!line)
		return (NULL);
	words = ft_split(line, FDF_FILE_DELIMITER);
	if (!words)
		return (free(line), NULL);
	result = malloc(sizeof(int) * count_words(line, FDF_FILE_DELIMITER));
	if (!result)
	{
		free_chartab(words);
		free(line);
		return (NULL);
	}
	index = 0;
	while (words[index])
	{
		result[index] = ft_atoi(words[index]);
		index++;
	}
	free_chartab(words);
	return (free(line), result);
}

t_list	*read_file(int fd)
{
	t_list 	*current;
	t_list	*temp;
	int		*values;
	
	current = NULL;
	values = parse_line(get_next_line(fd));
	while (values)
	{
		temp = ft_lstnew(values);
		if (!temp)
		{
			ft_lstclear(&current, free);
			free(values);
			return (NULL);
		}
		ft_lstadd_back(&current, temp);
		values = parse_line(get_next_line(fd));
	}
	return current;
}
