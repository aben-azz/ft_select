/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 04:02:50 by midrissi          #+#    #+#             */
/*   Updated: 2019/02/27 04:04:02 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_percent(int start, int end, int curr)
{
	double placement;
	double distance;

	placement = curr - start;
	distance = end - start;
	return (!distance ? 1.0 : (placement / distance));
}
