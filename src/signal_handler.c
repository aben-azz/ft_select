/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:36:11 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/21 18:59:01 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Handler for CTRL+C signal in idle status.
*/

static	void	sigint_handler(int sig)
{
	if (sig == SIGINT || sig == SIGABRT || sig == SIGSTOP
			|| sig == SIGKILL || sig == SIGQUIT)
	{
		ft_putstr(tparm(tgetstr("cm", NULL), 0, 0));
		ft_putstr(tgetstr("cd", NULL));
		ft_reset();
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
		i = ioctl(2, TIOCGWINSZ, w);
		g_global->tcap->xmax = (i ? tgetnum("co") : w->ws_col) - 1;
		g_global->tcap->ymax = (i ? tgetnum("li") : w->ws_row) - 1;
		free(w);
		print_argv(g_global->tcap);
	}
}

static void		bg(int sig)
{
	(void)sig;
	if (!isatty(1))
		return ;
	tcsetattr(0, TCSANOW, g_global->term_backup);
	ft_termcap(g_global->tcap->set_cursor);
	signal(SIGTSTP, SIG_DFL);
	ioctl(2, TIOCSTI, "\x1A");
}

static void		fg(int sig)
{
	struct winsize	*w;
	int				i;

	(void)sig;
	ft_printf("fg\n");
	if (!(w = ft_memalloc(sizeof(*w))))
		return ;
	tcsetattr(0, TCSANOW, g_global->term);
	signal(SIGTSTP, bg);
	i = ioctl(1, TIOCGWINSZ, w);
	g_global->tcap->xmax = (i ? tgetnum("co") : w->ws_col) - 1;
	g_global->tcap->ymax = (i ? tgetnum("li") : w->ws_row) - 1;
	free(w);
	ft_printf("f 2g\n");
	print_argv(g_global->tcap);
}

void			init_signal(void)
{
	signal(SIGCONT, fg);
	signal(SIGTSTP, bg);
	signal(SIGABRT, sigint_handler);
	signal(SIGSTOP, sigint_handler);
	signal(SIGKILL, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
}
