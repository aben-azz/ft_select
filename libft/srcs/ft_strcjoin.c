/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:56:22 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/29 18:15:43 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(char const *s1, char const *s2, char c)
{
	size_t	size;
	int		i;
	char	*fresh;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	fresh = (char *)malloc(sizeof(char) * size);
	if (!fresh)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		fresh[i] = s1[i];
		i++;
	}
	fresh[i] = c;
	fresh[i + 1] = '\0';
	ft_strcat(fresh, s2);
	return (fresh);
}
