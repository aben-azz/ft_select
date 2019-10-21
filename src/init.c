/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:50:33 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/21 17:02:31 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static inline void	init_tcap_str(t_cap *tcap)
{
	tcap->up = tgetstr("up", NULL);
	tcap->down = tgetstr("sf", NULL);
	tcap->right = tgetstr("nd", NULL);
	tcap->left = tgetstr("le", NULL);
	tcap->carriage = tgetstr("cr", NULL);
	tcap->clr_curr_line = tgetstr("ce", NULL);
	tcap->clr_all_line = tgetstr("cd", NULL);
	tcap->sound = tgetstr("bl", NULL);
	tcap->reset = tgetstr("me", NULL);
	tcap->underline = tgetstr("us", NULL);
	tcap->reverse_mode = tgetstr("mr", NULL);
	tcap->unset_cursor = tgetstr("vi", NULL);
	tcap->set_cursor = tgetstr("ve", NULL);
}

int					ft_reset(void)
{
	if (g_global->tcap->selected)
		free(g_global->tcap->selected);
	if (g_global->tcap->data)
		ft_splitdel(g_global->tcap->data);
	if (g_global)
		free(g_global);
	tcsetattr(0, TCSANOW, g_global->term_backup);
	ft_termcap(g_global->tcap->set_cursor);
	return (0);
}

int					init_tcap_variables(t_cap *tcap, char **argv)
{
	int i;

	i = -1;
	init_tcap_str(tcap);
	if (!(tcap->selected = ft_memalloc(sizeof(int ) * (tcap->size))))
		return (0);
	if (!(tcap->data = ft_splitdup(++argv)))
		return (0);
	while (++i < tcap->size)
		tcap->selected[i] = 0;
	tcap->max_len = 0;
	tcap->focus = 0;
	tcap->selected[0] = 0;
	i = -1;
	while (tcap->data[++i])
		tcap->max_len = ft_max(ft_strlen(tcap->data[i]), tcap->max_len);
	return (1);
}

int					init_tcap(t_term *term, t_cap *tcap, int argc,
		t_term *term_backup)
{
	struct winsize	*w;
	int				i;

	if (!~tcgetattr(0, term) || !~tcgetattr(0, term_backup))
		return (0);
	if (!(g_global = ft_memalloc(sizeof(*g_global))))
		return (0);
	g_global->term = term;
	g_global->term_backup = term_backup;
	g_global->tcap = tcap;
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (!~tcsetattr(0, TCSANOW, term) || !(w = ft_memalloc(sizeof(*w))))
		return (ft_reset());
	i = ioctl(1, TIOCGWINSZ, w);
	tcap->xmax = (i ? tgetnum("co") : w->ws_col) - 1;
	tcap->ymax = (i ? tgetnum("li") : w->ws_row) - 1;
	tcap->size = argc - 1;
	free(w);
	return (1);
}
