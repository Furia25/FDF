/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:14:20 by vdurand           #+#    #+#             */
/*   Updated: 2025/01/07 15:44:59 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	count_words(const char *str, char c)
{
	int	i;
	int	next;
	int	words;

	words = 0;
	next = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			next = 1;
		else if (next)
		{
			words++;
			next = 0;
		}
		i++;
	}
	return (words);
}

static void	*secure_free(char **tab, int index)
{
	while (index-- > 0)
		free(tab[index]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		last;
	int		i;
	int		wi;

	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	wi = -1;
	i = -1;
	last = -1;
	while (s[++i])
	{
		if (s[i] != c && s[i + 1])
			continue ;
		if (i - last > 1 || (!s[i + 1] && s[i] != c))
		{
			result[++wi] = ft_substr(s, last + 1, (i - (1 * s[i] == c)) - last);
			if (!result[wi])
				return (secure_free(result, (int) wi));
		}
		last = i;
	}
	result[++wi] = 0;
	return (result);
}

/*    int	main(int argc, char *argv[])
{
	char	*test = "split  ||this|for|me|||||!|";
	char	**t;
	char	**t2;

	t = ft_split(argv[1], '-');
	int i = 0;
	while (t[i])
	{
		puts(t[i]);
		i++;
	}
} */
