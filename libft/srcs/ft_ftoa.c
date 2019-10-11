/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:09:19 by midrissi          #+#    #+#             */
/*   Updated: 2019/02/10 21:35:43 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double		round_num(long double d, int precision)
{
	long double		diviseur;

	diviseur = 5;
	if (!precision)
		return (d + (d > 0.0 ? 0.5 : -0.5));
	while (precision-- >= 0)
		diviseur /= 10;
	return (d + (d > 0.0 ? diviseur : -diviseur));
}

static	char			*full_num(long double save,
							char **decimal, int prec, int signe)
{
	char *str;
	char *integer;

	integer = ft_itoa((long long)save);
	if (signe && integer && integer[0] != '-')
	{
		str = integer;
		integer = ft_strjoin("-", integer);
		ft_strdel(&str);
	}
	if (prec == -2)
	{
		ft_strdel(decimal);
		return (integer);
	}
	str = ft_strjoin(integer, *decimal);
	ft_strdel(&integer);
	ft_strdel(decimal);
	return (str);
}

char					*ft_ftoa(long double d, int precision)
{
	int					i;
	long double			save;
	char				*str;
	int					signe;

	signe = (d < 0 && d > -1);
	d = round_num(d, precision);
	save = d;
	d -= (long long)d;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (precision + 2))))
		return (NULL);
	str[precision + 1] = '\0';
	str[i++] = '.';
	d = d < 0 ? -d : d;
	precision = !precision ? -1 : precision;
	while (precision-- > 0)
	{
		d *= 10.0;
		str[i++] = (long long)d + 48;
		d -= (long long)d;
	}
	return (full_num(save, &str, precision, signe));
}
