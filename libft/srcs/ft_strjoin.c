/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:54:52 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/27 22:40:04 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	int		i;
	char	*fresh;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	fresh = (char *)malloc(sizeof(char) * size);
	if (!fresh)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		fresh[i] = s1[i];
		i++;
	}
	fresh[i] = '\0';
	ft_strcat(fresh, s2);
	return (fresh);
}
