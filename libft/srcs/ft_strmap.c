/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:20:20 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/11 12:51:50 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	size;
	size_t	i;
	char	*fresh;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	fresh = (char *)malloc(sizeof(char) * (size + 1));
	if (!fresh)
		return (NULL);
	i = 0;
	while (i < size)
	{
		fresh[i] = f(s[i]);
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
