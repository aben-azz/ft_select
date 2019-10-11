/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:11:05 by midrissi          #+#    #+#             */
/*   Updated: 2019/02/20 06:16:54 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		handle_char(t_format *fmt, va_list ap)
{
	char	c;

	if (fmt->conversion == 'c')
		c = (char)va_arg(ap, int);
	else
		c = '%';
	if (fmt->minus)
	{
		ft_putchar(c);
		ft_nputchar(' ', fmt->width - 1);
	}
	else
	{
		ft_nputchar(fmt->zero ? '0' : ' ', fmt->width - 1);
		ft_putchar(c);
	}
	return (fmt->width > 0 ? fmt->width : 1);
}

int		handle_str(t_format *fmt, va_list ap)
{
	char	*str;
	int		ret;

	str = va_arg(ap, char*);
	str = !str ? "(null)" : str;
	if (fmt->precision >= 0 && ((size_t)fmt->precision < ft_strlen(str)))
	{
		str = ft_strsub(str, 0, (size_t)fmt->precision);
		fmt->precision = -5;
	}
	str == NULL ? exit(1) : NULL;
	ret = ft_strlen(str);
	if (fmt->minus)
	{
		ft_putstr(str);
		ft_nputchar(' ', fmt->width - ret);
	}
	else
	{
		ft_nputchar(fmt->zero ? '0' : ' ', fmt->width - ret);
		ft_putstr(str);
	}
	if (fmt->precision == -5)
		ft_strdel(&str);
	return (ret < fmt->width ? fmt->width : ret);
}

int		handle_numbers(t_format *fmt, va_list ap)
{
	char		*str;
	int			len;

	str = get_string(fmt, ap);
	if (!fmt->precision && str[0] == '0' && fmt->conversion != 'f')
	{
		if (fmt->conversion == 'x' || fmt->conversion == 'X')
			fmt->prefixe = 0;
		str[0] = '\0';
	}
	if (fmt->conversion != 'p')
		fmt->prefixe = *str == '0' ? 0 : fmt->prefixe;
	if (*str == '-')
		fmt->signe = *(str++);
	fmt->precision -= ft_strlen(str);
	fmt->precision = fmt->prefixe == 1 ? fmt->precision - 1 : fmt->precision;
	fmt->precision = fmt->precision < 0 ? 0 : fmt->precision;
	len = fmt->width - ft_strlen(str) - (fmt->signe ? 1 : 0) - fmt->precision;
	len -= fmt->prefixe;
	len = print_numbers(fmt, str, len);
	fmt->signe == '-' ? free(--str) : ft_strdel(&str);
	return (len);
}
