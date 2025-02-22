/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_managing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:57:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/02/03 15:40:08 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int	try_open_file(int *fd, char *file_path)
{
	if (!ft_strend(file_path, ".fdf"))
		return (0);
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

static t_vect3	*parse_line(char *line, int y, float factor)
{
	char		**words;
	t_vect3		*result;
	int			index;

	if (!line)
		return (NULL);
	words = ft_split(line, FDF_FILE_DELIMITER);
	if (!words)
		return (free(line), NULL);
	result = ft_calloc(
			count_words(line, FDF_FILE_DELIMITER) + 1, sizeof(t_vect3));
	if (!result)
		return (free_chartab(words), free(line), NULL);
	index = 0;
	while (words[index])
	{
		result[index] = (t_vect3){
			(float)y, -(((float) ft_atoi(words[index])) / factor), -index};
		index++;
	}
	result[index] = (t_vect3){-1, -1, -1};
	free_chartab(words);
	return (free(line), result);
}

void	read_file(float factor, t_fdf_data *data)
{
	t_list		*current;
	t_list		*temp;
	t_vect3		*values;
	size_t		z;

	ft_printf("\033[1;34mGENERATING WIREFRAME...\033[0m\n");
	current = NULL;
	z = 0;
	values = parse_line(get_next_line(data->file_fd), z, factor);
	while (values)
	{
		temp = ft_lstnew(values);
		if (!temp)
		{
			ft_lstclear(&current, free);
			free(values);
			return ;
		}
		ft_lstadd_back(&current, temp);
		z++;
		values = parse_line(get_next_line(data->file_fd), z, factor);
	}
	ft_printf("\033[1;92mWIREFRAME GENERATED!\033[0m\n");
	data->points = current;
}
