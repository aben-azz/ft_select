/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:40:54 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/11 12:38:59 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr1;
	const char	*ptr2;

	ptr1 = (char *)dst;
	ptr2 = (const char *)src;
	while (n > 0)
	{
		*ptr1++ = *ptr2++;
		n--;
	}
	return (dst);
}
