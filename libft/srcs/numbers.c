/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:12:40 by midrissi          #+#    #+#             */
/*   Updated: 2019/02/20 06:16:59 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t		get_signed(t_format *fmt, va_list ap)
{
	if (fmt->modifier == HH)
		return ((char)va_arg(ap, long long));
	else if (fmt->modifier == H)
		return ((short)va_arg(ap, long long));
	else if (fmt->modifier == L || fmt->modifier == LL)
		return (va_arg(ap, long long));
	else if (fmt->modifier == Z)
		return (va_arg(ap, size_t));
	else if (fmt->modifier == J)
		return (va_arg(ap, intmax_t));
	else
		return (va_arg(ap, int));
	return (0);
}

uintmax_t		get_unsigned(t_format *fmt, va_list ap)
{
	if (fmt->modifier == L || fmt->modifier == LL
			|| fmt->conversion == 'p')
		return (va_arg(ap, unsigned long long));
	else if (fmt->modifier == H)
		return ((unsigned short)va_arg(ap, unsigned long long));
	else if (fmt->modifier == HH)
		return ((unsigned char)va_arg(ap, unsigned long long));
	else if (fmt->modifier == Z)
		return (va_arg(ap, size_t));
	else if (fmt->modifier == J)
		return (va_arg(ap, uintmax_t));
	else
		return (va_arg(ap, unsigned int));
	return (0);
}

static int		print_prefixe(char c)
{
	int i;

	i = 0;
	c = c == 'p' ? 'x' : c;
	if (c == 'o' || c == 'x' || c == 'X')
	{
		ft_putchar('0');
		i++;
	}
	if (c == 'x' || c == 'X')
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

int				print_numbers(t_format *fmt, char *str, int len)
{
	int ret;

	ret = 0;
	if (fmt->minus)
	{
		fmt->signe ? ft_putchar(fmt->signe) : NULL;
		if (fmt->prefixe)
			ret = print_prefixe(fmt->conversion);
		ft_nputchar('0', fmt->precision);
		ft_putstr(str);
		ft_nputchar(' ', len);
	}
	else
	{
		!fmt->zero ? ft_nputchar(' ', len) : NULL;
		fmt->signe ? ft_putchar(fmt->signe) : NULL;
		if (fmt->prefixe)
			ret = print_prefixe(fmt->conversion);
		fmt->zero ? ft_nputchar(fmt->zero, len) : NULL;
		ft_nputchar('0', fmt->precision);
		ft_putstr(str);
	}
	len = len < 0 ? 0 : len;
	return (ret + ft_strlen(str) + len + fmt->precision + (fmt->signe != 0));
}

char			*get_string(t_format *fmt, va_list ap)
{
	char *str;
	char *temp;

	str = NULL;
	temp = NULL;
	if (fmt->conversion == 'f')
	{
		if (fmt->modifier == LU)
			str = ft_ftoa(va_arg(ap, long double), fmt->precision);
		else
			str = ft_ftoa(va_arg(ap, double), fmt->precision);
		if (str && fmt->prefixe && !ft_strchr(str, '.') && (temp = str))
			str = ft_strjoin(str, ".");
		ft_strdel(&temp);
		fmt->precision = 0;
		fmt->prefixe = 0;
	}
	else if (fmt->conversion == 'd' || fmt->conversion == 'i')
		str =
		ft_itoa_base(get_signed(fmt, ap), fmt->base, !(fmt->conversion > 96));
	else
		str =
		ft_utoa_base(get_unsigned(fmt, ap), fmt->base, !(fmt->conversion > 96));
	str == NULL ? exit(1) : NULL;
	return (str);
}
