/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:43:56 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/15 15:53:56 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_split_count(const char **split)
{
	int i;

	i = 0;
	if (split)
	{
		while (split[i])
			i++;
	}
	return (i);
}
