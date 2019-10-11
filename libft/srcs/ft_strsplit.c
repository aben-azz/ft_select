/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 13:42:50 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/14 03:47:31 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_substr_len(char const *s, int start, char c)
{
	size_t len;

	len = 0;
	while (s[start] && s[start] != c)
	{
		start++;
		len++;
	}
	return (len);
}

static void		free_mem(char **strings, int len)
{
	int i;

	i = 0;
	while (i <= len)
	{
		free(strings[i++]);
	}
	free(strings);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**strings;
	int		count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	strings = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i - 1] == c || i == 0) && j < count)
			if (!(strings[j++] = ft_strsub(s, i, get_substr_len(s, i, c))))
			{
				free_mem(strings, j - 2);
				return (NULL);
			}
		i++;
	}
	strings[j] = 0;
	return (strings);
}
