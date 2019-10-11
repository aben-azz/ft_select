/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:23:27 by midrissi          #+#    #+#             */
/*   Updated: 2019/09/28 06:24:41 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *orig, char *rep, char *with)
{
	char	*result;
	char	*ins;
	char	*tmp;
	int		len[4];

	if (!orig || !rep || !(len[0] = ft_strlen(rep)) || !ft_strstr(orig, rep))
		return (!ft_strstr(orig, rep) ? ft_strdup(orig) : NULL);
	len[0] = ft_strlen(rep);
	!with ? (with = " ") : NULL;
	len[1] = ft_strlen(with);
	ins = orig;
	len[3] = 0;
	while ((tmp = ft_strstr(ins, rep)) && ++len[3])
		ins = tmp + len[0];
	if (!(result = malloc(strlen(orig) + (len[1] - len[0]) * len[3] + 1)))
		return (NULL);
	tmp = result;
	while (len[3]-- && (ins = ft_strstr(orig, rep)))
	{
		len[2] = ins - orig;
		tmp = ft_strncpy(tmp, orig, len[2]) + len[2];
		tmp = ft_strcpy(tmp, with) + len[1];
		orig += len[2] + len[0];
	}
	return (ft_strjoin(result, orig));
}
