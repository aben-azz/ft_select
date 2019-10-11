/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 03:59:17 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/21 11:53:19 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int				ft_get_color(int color1, int color2, double percentage)
{
	int		red;
	int		green;
	int		blue;

	red = get_light((color1 >> 16) & 0xFF,
			(color2 >> 16) & 0xFF, percentage);
	green = get_light((color1 >> 8) & 0xFF,
			(color2 >> 8) & 0xFF, percentage);
	blue = get_light(color1 & 0xFF, color2 & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
