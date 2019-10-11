/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 13:12:22 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/14 14:57:52 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == '\t' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	int			i;
	char		*fresh;
	char const	*ptr;

	if (!s)
		return (NULL);
	ptr = s;
	while (*ptr && is_space(*ptr))
		ptr++;
	i = ft_strlen(ptr) - 1;
	while (i >= 0 && is_space(ptr[i]))
		i--;
	if (!(fresh = (char *)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	fresh[0] = '\0';
	ft_strncat(fresh, ptr, (size_t)(i + 1));
	return (fresh);
}
