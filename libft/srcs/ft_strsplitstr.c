/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:18:09 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/26 13:30:09 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_substr_len(char const *s, int start, char *needle)
{
	size_t len;

	len = 0;
	while (s[start] && !ft_strchr(needle, s[start]))
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

char			**ft_strsplitstr(char const *s, char *needle)
{
	char	**strings;
	int		count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	count = ft_count_words_str(s, needle);
	strings = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (!ft_strchr(needle, s[i]) &&
						(ft_strchr(needle, s[i - 1]) || i == 0) && j < count)
			if (!(strings[j++] = ft_strsub(s, i, get_substr_len(s, i, needle))))
			{
				free_mem(strings, j - 2);
				return (NULL);
			}
	strings[j] = 0;
	return (strings);
}
