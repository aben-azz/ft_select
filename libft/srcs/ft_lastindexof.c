/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastindexof.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 04:14:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 04:18:19 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lastindexof(char *string, char c)
{
	int i;
	int j;

	j = ft_strlen(string);
	i = 0;
	while (string[--j])
	{
		if (string[j] == c)
			return (j);
	}
	return (-1);
}
