/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:11:52 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/11 12:23:01 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (n == 0)
		return (0);
	i = 0;
	n--;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (ptr1[i] && ptr2[i] && ptr1[i] == ptr2[i] && i < n)
		i++;
	return (ptr1[i] - ptr2[i]);
}
