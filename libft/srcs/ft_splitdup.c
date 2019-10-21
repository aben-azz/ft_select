/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:33:14 by midrissi          #+#    #+#             */
/*   Updated: 2019/10/21 17:05:19 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_mem(char **strings, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(strings[i++]);
	free(strings);
}

char			**ft_splitdup(char **src)
{
	char	**new;
	int		i;
	int		size;

	if (!src)
		return (NULL);
	i = -1;
	size = ft_split_count((const char **)src);
	new = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	while (src[++i])
		if (!(new[i] = ft_strdup(src[i])))
		{
			free_mem(new, i);
			return (NULL);
		}
	new[i] = NULL;
	return (new);
}
