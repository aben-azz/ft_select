/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 10:11:38 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/21 11:26:31 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *src, int m, int n)
{
	int		len;
	char	*dest;
	int		i;

	len = n - m;
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = m;
	while (i < n && (*src != '\0'))
	{
		*dest = *(src + i++);
		dest++;
	}
	*dest = '\0';
	return (dest - len);
}
