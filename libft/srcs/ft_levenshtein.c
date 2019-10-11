/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_levenshtein.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 04:01:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/12 02:10:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	*loop_levenshtein(size_t index[2], size_t length)
{
	size_t *cache;

	if (!(cache = malloc(length * sizeof(size_t))))
		return (NULL);
	index[0] = 0;
	index[1] = 0;
	while (index[0] < length)
		(cache[index[0]] = index[0] + 1) && (index[0]++);
	return (cache);
}

size_t			ft_levenshtein_n(char *a, size_t length, char *b, size_t blen)
{
	size_t	*cache;
	size_t	index[2];
	size_t	dist[3];
	char	code;

	if (!(cache = loop_levenshtein(index, length)) || (!length || !blen))
		return (!cache ? -1 : 0);
	while (index[1] < blen)
	{
		code = b[index[1]];
		dist[0] = index[1]++;
		dist[2] = dist[0];
		index[0] = SIZE_MAX;
		while (++index[0] < length)
		{
			dist[1] = dist[0] += code != a[index[0]];
			if ((dist[0] = cache[index[0]]) > dist[2])
				cache[index[0]] = (dist[1] > dist[2]) ? dist[2] + 1 : dist[1];
			else
				cache[index[0]] = (dist[1] > dist[0]) ? dist[0] + 1 : dist[1];
			dist[2] = cache[index[0]];
		}
	}
	free(cache);
	return (dist[2]);
}

size_t			ft_levenshtein(char *a, char *b)
{
	return (ft_levenshtein_n(a, ft_strlen(a), b, ft_strlen(b)));
}
