/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/14 02:21:08 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>

t_global	*g_global;

static	inline	int	init_tcap_variables(t_cap *tcap, char **argv)
{
	int i;

	i = -1;
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
	if (!(tcap->ignored = ft_memalloc(sizeof(int ) * (tcap->size + 1))))
		return (0);
	if (!(tcap->data = ft_splitdup(++argv)))
		return (0);
	while (++i < tcap->size)
		tcap->ignored[i] = 0;
	tcap->ignored[i] = -1;
	tcap->max_len = 0;
	tcap->focus = 0;
	tcap->selected = 0;
	i = -1;
	while (tcap->data[++i])
		tcap->max_len = ft_max(ft_strlen(tcap->data[i]), tcap->max_len);
	ft_printf("max_len == %d\n", tcap->max_len);
	return (1);
}

int		init_tcap(t_term *term, t_cap *tcap, int argc, t_term *term_backup)
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
	if (!~tcsetattr(0, TCSADRAIN, term) || !(w = ft_memalloc(sizeof(*w))))
		return (0);
	i = ioctl(1, TIOCGWINSZ, w);
	tcap->xmax = (!i ? tgetnum("co") : w->ws_col) - 1;
	tcap->ymax = (!i ? tgetnum("li") : w->ws_row) - 1;
	tcap->size = argc - 1;
	free(w);
	return (1);
}


/*
** void	sig_winch(int signal)
** {
** 	struct winsize	*w;
**
** 	if (signal == SIGWINCH)
** 	{
** 		ft_putstr(tparm(tgetstr("cm", NULL), 0, 0));
** 		ft_putstr(tgetstr("cd", NULL));
** 		i = ioctl(1, TIOCGWINSZ, w);
** 		tcap->xmax = (!i ? tgetnum("co") : w->ws_col) - 1;
** 		tcap->ymax = (!i ? tgetnum("li") : w->ws_row) - 1;
** 		tcap->size = argc - 1;
** 		free(w);
** 		exit(0);
** 	}
** }
*/

void read_arrows(char touche[2], t_cap *tcap)
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

int		ft_move(t_cap *tcap, char *string, int n)
{
	while (n--)
	{
		if (!ft_strcmp(string, "down"))
			ft_putstr(tcap->down);
		else if (!ft_strcmp(string, "left"))
			ft_putstr(tcap->left);
		else if (!ft_strcmp(string, "right"))
			ft_putstr(tcap->right);
		else if (!ft_strcmp(string, "up"))
			ft_putstr(tcap->up);
	}
	return (1);
}

void	print_file_name(char **string, t_cap *tcap, int i)
{
	if (tcap->selected == i)
		ft_putstr(tcap->reverse_mode);
	if (tcap->focus == i)
		ft_putstr(tcap->underline);
	ft_putstr(string[i]);
	ft_putstr(tcap->reset);
	ft_move(tcap, "right", tcap->max_len - ft_strlen(string[i]) + 2);
}

int	print_argv(t_cap *tcap)
{
	int c;
	int r;
	int i;

	i = 0;
	c = -1;
	ft_putstr(tparm(tgetstr("cm", NULL), 0, 0));
	ft_putstr(tcap->clr_all_line);
	tcap->row = tcap->xmax / ft_max(tcap->max_len + 2, 1);
	tcap->row = ft_min(tcap->size, tcap->row);
	tcap->column = tcap->size / ft_max(tcap->row, 1);
	tcap->carry = tcap->size % ft_max(tcap->row, 1);
	//ft_printf("{%d, %d}, row: %d, column: %d, carry: %d, max_len: %d, size: %d\n", tcap->xmax, tcap->ymax, row, column, carry, tcap->max_len, tcap->size);
	while (++c < tcap->column)
	{
		r = -1;
		while (++r < tcap->row)
			print_file_name(tcap->data, tcap, i++);
		ft_move(tcap, "down", 1);
	}
	if (tcap->carry)
		while (tcap->data[i])
			print_file_name(tcap->data, tcap, i++);
	ft_putstr(tparm(tgetstr("cm", NULL), -1, -1));
	return (1);
}

int		main(int ac, char **av)
{
	t_term	term;
	t_term	term_backup;
	char	buffer[2];
	char	touche[2];
	t_cap	tcap;

	if (!(tgetent(NULL, getenv("TERM"))) || !init_tcap(&term, &tcap, ac,
		&term_backup) || !init_tcap_variables(&tcap, av))
	{
		tcsetattr(0, TCSADRAIN, &term_backup);
		return (1);
	}
	init_signal();
	print_argv(&tcap);
	while (19)
	{
		ft_bzero(buffer, 2);
		read(0, &buffer, 1);
		if (buffer[0] == 27)
		{
			ft_bzero(touche, 2);
			read(0, touche, 2);
			read_arrows(touche, &tcap);
		}
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d\n");
			return (0);
		}
	}
	return (0);
}
