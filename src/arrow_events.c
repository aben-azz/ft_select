/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 21:32:07 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/19 16:06:59 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		arrow_up_event(t_cap *tcap)
{
	int		x;

	if (tcap->focus - tcap->row > -1)
		tcap->focus -= tcap->row;
	else
	{
		if ((x = tcap->focus % ft_max(tcap->row, 1)) < tcap->carry)
		{
			tcap->focus = tcap->size - 1;
			if (tcap->focus)
				tcap->focus -= tcap->carry - x - 1;
		}
		else
		{
			tcap->focus = tcap->size - 1;
			tcap->focus -= tcap->carry;
			tcap->focus -= tcap->row - x - 1;
		}
	}
	return (print_argv(tcap));
}

static int		arrow_down_event(t_cap *tcap)
{
	int		new_x;

	new_x = tcap->focus % ft_max(tcap->row, 1);
	if (tcap->focus + tcap->row < tcap->size)
		tcap->focus += tcap->row;
	else
	{
		if (new_x < tcap->carry)
			tcap->focus = new_x;
		else
			tcap->focus = new_x;
	}
	return (print_argv(tcap));
}

static int		arrow_right_event(t_cap *tcap)
{
	tcap->focus++;
	if (tcap->focus == tcap->size)
		tcap->focus = 0;
	return (print_argv(tcap));
}

static int		arrow_left_event(t_cap *tcap)
{
	tcap->focus--;
	if (tcap->focus == -1)
		tcap->focus = tcap->size - 1;
	return (print_argv(tcap));
}

void			read_arrows(char touche[2], t_cap *tcap)
{
	if (touche[1] == ARROW_UP)
		arrow_up_event(tcap);
	else if (touche[1] == ARROW_DOWN)
		arrow_down_event(tcap);
	else if (touche[1] == ARROW_LEFT)
		arrow_left_event(tcap);
	else if (touche[1] == ARROW_RIGHT)
		arrow_right_event(tcap);
}
