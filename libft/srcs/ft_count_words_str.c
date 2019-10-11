/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:24:53 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/26 13:28:58 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words_str(char const *s, char *needle)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_strchr(needle, s[i]) && (ft_strchr(needle, s[i - 1]) || i == 0))
			count++;
		i++;
	}
	return (count);
}
