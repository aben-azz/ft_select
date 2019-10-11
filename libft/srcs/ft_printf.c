/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:10:48 by midrissi          #+#    #+#             */
/*   Updated: 2019/02/20 06:17:14 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		set_conversion(char *str, t_format *fmt)
{
	fmt->modifier = 0;
	while (*str)
	{
		if (ft_strchr(CONV, *str))
		{
			fmt->conversion = *str;
			if (ft_strchr("DOU", fmt->conversion))
			{
				fmt->modifier = L;
				fmt->conversion = ft_tolower(fmt->conversion);
			}
			fmt->base = 10;
			if (fmt->conversion == 'x' || fmt->conversion == 'X'
				|| fmt->conversion == 'p')
				fmt->base = 16;
			fmt->base = fmt->conversion == 'o' ? 8 : fmt->base;
			fmt->base = fmt->conversion == 'b' ? 2 : fmt->base;
			return ;
		}
		str++;
	}
	fmt->conversion = 0;
}

int			check_conversion(char **str)
{
	while (**str && !ft_strchr(CONV, **str))
	{
		if (!ft_strchr("-+ #0lLhzj*.", **str) && !ft_isdigit(**str))
			return (0);
		(*str)++;
	}
	if (!(**str))
		return (0);
	(*str)++;
	return (1);
}

t_format	*create_format(char *str, va_list ap)
{
	t_format	*fmt;

	if (!(fmt = (t_format *)malloc(sizeof(t_format))))
		exit(1);
	fmt->minus = 0;
	set_conversion(str, fmt);
	fmt->width = get_width(str, ap, fmt);
	fmt->precision = get_precision(str, fmt, ap);
	if (!fmt->modifier)
		fmt->modifier = get_modifier(str, fmt);
	set_flags(str, fmt);
	if (ft_strchr("diouxXbp", fmt->conversion) && fmt->precision != -1)
		fmt->zero = 0;
	if (fmt->conversion == 'c' || fmt->conversion == '%')
		fmt->handler = &handle_char;
	else if (fmt->conversion == 's')
		fmt->handler = &handle_str;
	else
		fmt->handler = &handle_numbers;
	return (fmt);
}

int			parse_format(char *str, va_list ap)
{
	t_format	*fmt;
	int			ret;

	ret = 0;
	while (*str)
	{
		if (*str == '%')
		{
			fmt = create_format(++str, ap);
			if (check_conversion(&str))
				ret += fmt->handler(fmt, ap);
			free(fmt);
		}
		else
		{
			write(1, str++, 1);
			ret++;
		}
	}
	return (ret);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = parse_format((char *)format, ap);
	va_end(ap);
	return (ret);
}
