/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:53:33 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/21 17:32:07 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					ft_termcap(char *str)
{
	ft_putstr_fd(str, 2);
}

static inline void		free_tab_i(char **strings, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(strings[i++]);
	free(strings);
}

static inline void		remove_data(t_cap *tcap, int exception)
{
	char	**new;
	int		i;
	int		size;
	int		j;

	i = -1;
	j = 0;
	size = ft_split_count((const char **)tcap->data);
	if (!(new = ft_memalloc(sizeof(char *) * (size))))
		return ;
	while (tcap->data[++i])
	{
		if (i == exception)
			continue;
		if (!(new[j++] = ft_strdup(tcap->data[i])))
		{
			free_tab_i(new, i);
			return ;
		}
	}
	new[j] = NULL;
	ft_splitdel(tcap->data);
	tcap->size--;
	tcap->focus = ft_max(0, tcap->focus - 1);
	tcap->data = new;
}

int						read_keys(char touche, t_cap *tcap)
{
	if (touche == 4 || touche == ESC)
	{
		ft_termcap(tparm(tgetstr("cm", NULL), 0, 0));
		ft_termcap(tcap->clr_all_line);
		return (-1);
	}
	else if (touche == ENTER)
		return (return_selected(tcap));
	else if (touche == SPACE)
	{
		tcap->selected[tcap->focus] = !tcap->selected[tcap->focus];
		if (tcap->selected[tcap->focus])
			tcap->focus = ft_min(tcap->focus + 1, tcap->size - 1);
	}
	else if (touche == DEL || touche == BACKSPACE)
		remove_data(tcap, tcap->focus);
	print_argv(tcap);
	return (1);
}

int						ft_move(t_cap *tcap, char *string, int n)
{
	if (!string)
		return (0);
	while (n--)
	{
		if (!ft_strcmp(string, "down"))
			ft_termcap(tcap->down);
		else if (!ft_strcmp(string, "left"))
			ft_termcap(tcap->left);
		else if (!ft_strcmp(string, "right"))
			ft_termcap(tcap->right);
		else if (!ft_strcmp(string, "up"))
			ft_termcap(tcap->up);
	}
	return (1);
}
