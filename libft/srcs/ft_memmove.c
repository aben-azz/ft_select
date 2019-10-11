/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:05:23 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/12 12:08:33 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr1;
	unsigned char		*ptr2;
	size_t				i;

	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	i = 0;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		while (len > 0)
		{
			ptr1[len - 1] = ptr2[len - 1];
			len--;
		}
	return (dst);
}
