/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_geters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:23:27 by midrissi          #+#    #+#             */
/*   Updated: 2019/02/27 00:55:54 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			set_flags(char *str, t_format *fmt)
{
	fmt->zero = 0;
	fmt->minus = fmt->minus == '-' ? fmt->minus : 0;
	fmt->signe = 0;
	fmt->prefixe = 0;
	while (*str && !ft_strchr(CONV, *str))
	{
		if (*str == '0' && !ft_isdigit(*(str - 1)) && *(str - 1) != '.')
			fmt->zero = '0';
		if (*str == ' ' && !fmt->signe && ft_strchr("dif", fmt->conversion))
			fmt->signe = ' ';
		if (*str == '+' && ft_strchr("dif", fmt->conversion))
			fmt->signe = '+';
		fmt->minus = *str == '-' ? '-' : fmt->minus;
		if (*str == '#' && (fmt->conversion == 'o' || fmt->conversion == 'f'))
			fmt->prefixe = 1;
		if ((*str == '#' && (fmt->conversion == 'x' || fmt->conversion == 'X')))
			fmt->prefixe = 2;
		str++;
	}
	if (fmt->conversion == 'p')
		fmt->prefixe = 2;
}

static int		ft_count_modifiers(char c, char *str)
{
	int i;

	i = 0;
	while (*str && !ft_strchr(CONV, *str))
		i += (*(str++) == c);
	return (i);
}

int				get_modifier(char *str, t_format *fmt)
{
	int lcount;
	int hcount;

	lcount = ft_count_modifiers('l', str);
	hcount = ft_count_modifiers('h', str);
	if (fmt->conversion == 'f' && ft_count_modifiers('L', str) > 0)
		return (LU);
	if (ft_count_modifiers('j', str))
		return (J);
	if (ft_count_modifiers('z', str))
		return (Z);
	if (lcount && lcount % 2)
		return (L);
	if (lcount)
		return (LL);
	if (hcount && hcount % 2)
		return (H);
	return (hcount ? HH : 0);
}

int				get_precision(char *str, t_format *fmt, va_list ap)
{
	int precision;
	int point;

	point = 0;
	while (*str && !ft_strchr(CONV, *str))
	{
		if (*str == '.' && (point = 1) && str++)
		{
			precision = 0;
			(ft_isdigit(*str)) && (precision = ft_atoi(str));
			while (ft_isdigit(*str))
				str++;
			if (*str == '*' && *(str - 1) == '.' && str++)
			{
				precision = va_arg(ap, int);
				point = precision < 0 ? 0 : point;
			}
			continue;
		}
		str++;
	}
	(!point) && (precision = -1);
	if (!point && fmt->conversion == 'f')
		precision = 6;
	return (precision);
}

int				get_width(char *str, va_list ap, t_format *fmt)
{
	int width;
	int temp;

	width = 0;
	while (*str && !ft_strchr(CONV, *str))
	{
		if (*str == '.' && str++)
		{
			while (ft_isdigit(*str))
				str++;
			str += (*str == '*' && *(str - 1) == '.');
			continue;
		}
		(*str == '*') && (width = va_arg(ap, int));
		(*str == '*') && (fmt->minus = width < 0 ? '-' : 0);
		(*str == '*') && (width = ft_abs(width));
		if (ft_isdigit(*str) && (temp = ft_atoi(str)))
		{
			width = temp;
			while (ft_isdigit(*(str + 1)))
				str++;
		}
		str++;
	}
	return (width);
}
