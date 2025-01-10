/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_managing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:57:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/10 13:50:48 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int	try_open_file(int *fd, char *file_path)
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

static t_vect3	*parse_line(char *line, int y)
{
	char		**words;
	t_vect3	*result;
	size_t		index;

	if (!line)
		return (NULL);
	words = ft_split(line, FDF_FILE_DELIMITER);
	if (!words)
		return (free(line), NULL);
	result = ft_calloc(count_words(line, FDF_FILE_DELIMITER) + 1, sizeof(t_vect3));
	if (!result)
	{
		free_chartab(words);
		free(line);
		return (NULL);
	}
	index = 0;
	while (words[index])
	{
		result[index] = (t_vect3){index,y,(float) ft_atoi(words[index]) / 3};
		index++;
	}
	result[index] = (t_vect3){-1, -1, -1};
	free_chartab(words);
	return (free(line), result);
}

t_list	*read_file(int fd)
{
	t_list		*current;
	t_list		*temp;
	t_vect3		*values;
	float		y;

	ft_printf("\033[1;34mGENERATING WIREFRAME...\033[0m\n");
	current = NULL;
	y = 0;
	values = parse_line(get_next_line(fd), y);
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
		values = parse_line(get_next_line(fd), y);
		y ++;
	}
	ft_printf("\033[1;92mWIREFRAME GENERATED!\033[0m\n");
	return (current);
}
