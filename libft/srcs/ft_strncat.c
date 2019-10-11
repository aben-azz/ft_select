/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:57:01 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/08 14:59:26 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t len)
{
	size_t	i;
	int		s1_end;

	i = 0;
	s1_end = ft_strlen(s1);
	while (s2[i] && i < len)
		s1[s1_end++] = s2[i++];
	s1[s1_end] = '\0';
	return (s1);
}
