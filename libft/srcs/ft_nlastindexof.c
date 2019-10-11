/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nlastindexof.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 04:14:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/30 05:22:56 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nlastindexof(char *string, char c, int n)
{
	int i;
	int j;

	j = ft_strlen(string) - n;
	i = 0;
	while (string[--j])
	{
		if (string[j] == c)
			return (j);
	}
	return (-1);
}
