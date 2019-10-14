/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 04:55:03 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/14 05:33:24 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_select.h"

int		ft_termcap(int c)
{
	return (write(0, &c, 1));
}

int			debug(void)
{
	int fd;

	return (fd = open("log.log", O_RDWR | O_APPEND | O_CREAT, 0666));
}

/*
** static	inline	int	init_tcap_variables(t_cap *tcap, char **argv)
** {
** 	int i;
**
** 	i = -1;
** 	tcap->up = tgetstr("up", NULL);
** 	tcap->down = tgetstr("sf", NULL);
** 	tcap->right = tgetstr("nd", NULL);
** 	tcap->left = tgetstr("le", NULL);
** 	tcap->carriage = tgetstr("cr", NULL);
** 	tcap->clr_curr_line = tgetstr("ce", NULL);
** 	tcap->clr_all_line = tgetstr("cd", NULL);
** 	tcap->sound = tgetstr("bl", NULL);
** 	tcap->reset = tgetstr("me", NULL);
** 	tcap->underline = tgetstr("us", NULL);
** 	tcap->reverse_mode = tgetstr("mr", NULL);
** 	if (!(tcap->selected = ft_memalloc(sizeof(int ) * (tcap->size))))
** 		return (0);
** 	if (!(tcap->data = ft_splitdup(++argv)))
** 		return (0);
** 	while (++i < tcap->size)
** 		tcap->selected[i] = 0;
** 	tcap->max_len = 0;
** 	tcap->focus = 0;
** 	tcap->selected[0] = 1;
** 	i = -1;
** 	while (tcap->data[++i])
** 		tcap->max_len = ft_max(ft_strlen(tcap->data[i]), tcap->max_len);
** 	return (1);
** }
*/

int		init_tcap(t_term *term, t_cap *tcap, int argc, t_term *term_backup)
{
	struct winsize	*w;
	int				i;

	if (!~tcgetattr(0, term) || !~tcgetattr(0, term_backup))
		return (0);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (!~tcsetattr(0, TCSANOW, term) || !(w = ft_memalloc(sizeof(*w))))
		return (0);
	i = ioctl(1, TIOCGWINSZ, w);
	tcap->xmax = (!i ? tgetnum("co") : w->ws_col) - 1;
	tcap->ymax = (!i ? tgetnum("li") : w->ws_row) - 1;
	tcap->size = argc - 1;
	free(w);
	return (1);
}

int		main(int ac, char **av)
{
	t_term	term;
	t_term	term_backup;
	char	buffer[4];
	t_cap	tcap;
	int a = 0;
	if (!(tgetent(NULL, getenv("TERM"))) || !init_tcap(&term, &tcap, ac,
		&term_backup))
	{
		tcsetattr(0, TCSANOW, &term_backup);
		return (1);
	}
	while ("ft_select")
	{
		tputs(tgetstr("vi", NULL), 1, ft_termcap);
		if (a) tputs(tgetstr("mr", NULL), 1, ft_termcap);
		tputs(tgetstr("cl", NULL), 1, ft_termcap);
		tputs(tgetstr("us", NULL), 1, ft_termcap);
		ft_putstr_fd("coucou", 0);
		tputs(tgetstr("me", NULL), 1, ft_termcap);
		tputs(tgetstr("sf", NULL), 1, ft_termcap);

		if (!a) tputs(tgetstr("mr", NULL), 1, ft_termcap);
		tputs(tgetstr("us", NULL), 1, ft_termcap);
		ft_putstr_fd("coucou xd", 0);
		tputs(tgetstr("me", NULL), 1, ft_termcap);
		read(0, buffer, 3);
		if (buffer[0] == ENTER)
		{
			tputs(tgetstr("cl", NULL), 1, ft_termcap);
			ft_printf("oui mon pote");
			tputs(tgetstr("ve", NULL), 1, ft_termcap);
			return (0);
		} else if (buffer[0] == SPACE)
			a = !a;
	}
	return (0);
}
