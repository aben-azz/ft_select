/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:36:11 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/19 16:08:41 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Handler for CTRL+C signal in idle status.
*/

static	void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr(tparm(tgetstr("cm", NULL), 0, 0));
		ft_putstr(tgetstr("cd", NULL));
		tcsetattr(0, TCSADRAIN, g_global->term_backup);
		ft_termcap(g_global->tcap->set_cursor);
		exit(0);
	}
}

static	void	sigwinch_handler(int signal)
{
	struct winsize	*w;
	int				i;

	if (signal == SIGWINCH)
	{
		if (!(w = ft_memalloc(sizeof(*w))))
			return ;
		ft_putstr(tparm(tgetstr("cm", NULL), 0, 0));
		ft_putstr(tgetstr("cd", NULL));
		i = !ioctl(1, TIOCGWINSZ, w);
		g_global->tcap->xmax = (!i ? tgetnum("co") : w->ws_col) - 1;
		g_global->tcap->ymax = (!i ? tgetnum("li") : w->ws_row) - 1;
		free(w);
		print_argv(g_global->tcap);
	}
}

/*
** Handler for CTRL+Z in idle status.
*/

static	void	sigtstp_handler(int sig)
{
	if (sig == SIGTSTP)
	{
		signal(SIGTSTP, sigtstp_handler);
	}
}

static	void	sigstp_handler(int sig)
{
	if (sig == SIGTSTP)
	{
		signal(SIGTSTP, sigstp_handler);
	}
}

void			init_signal(void)
{
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGTSTP, sigstp_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
}
