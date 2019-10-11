/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:55:01 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/09 17:03:49 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!ft_strlen(needle))
		return ((char *)haystack);
	while (*haystack && i < len)
	{
		j = 0;
		while (haystack[j] == needle[j] && (j + i) < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack);
		}
		i++;
		haystack++;
	}
	return (NULL);
}
