/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/13 21:38:42 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>

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

int		init_tcap(t_term *term, t_cap *tcap, int argc, char **argv)
{
	struct winsize	*w;
	int				i;

	if (!~tcgetattr(0, term))
		return (0);
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
	return (init_tcap_variables(tcap, argv));
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("on quitte\n");
		exit(0);
	}
}

void display_prompt()
{
	ft_printf("\x1b[32m$ft_select>\x1b[0m ");
}

void read_arrows(char touche[2], int shift, t_cap *tcap)
{
	if (shift)
	{
		if (touche[1] == ARROW_UP)
			ft_printf("{LU}\n");
		else if (touche[1] == ARROW_DOWN)
			ft_printf("{LD}\n");
		else if (touche[1] == ARROW_LEFT)
			ft_printf("{LL}\n");
		else if (touche[1] == ARROW_RIGHT)
			ft_printf("{LR}\n");
	}
	else
	{
		if (touche[1] == ARROW_UP)
			arrow_up_event(tcap);
		else if (touche[1] == ARROW_DOWN)
			arrow_down_event(tcap);
		else if (touche[1] == ARROW_LEFT)
			arrow_left_event(tcap);
		else if (touche[1] == ARROW_RIGHT)
			arrow_right_event(tcap);
		if (touche[1] == ARROW_UP || touche[1] == ARROW_DOWN ||
				touche[1] == ARROW_LEFT || touche[1] == ARROW_RIGHT)
			;//display_prompt();
	}
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

int	print_argv(t_cap *tcap)
{
	int x;
	int y;
	int c;
	int r;
	int i;

	i = 0;
	x = 0;
	y = 0;
	c = -1;
	ft_putstr(tparm(tgetstr("cm", NULL), y, x));
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
		{
			if (tcap->selected == i)
				ft_putstr(tcap->reverse_mode);
			if (tcap->focus == i)
				ft_putstr(tcap->underline);
			ft_putstr(tcap->data[i]);
			ft_putstr(tcap->reset);
			ft_move(tcap, "right", tcap->max_len - ft_strlen(tcap->data[i]) + 2);
			i++;
		}
		if (tcap->column > 1)
			ft_move(tcap, "down", 1);
	}
	if (tcap->carry)
		while (tcap->data[i])
		{
			if (tcap->selected == i)
				ft_putstr(tcap->reverse_mode);
			if (tcap->focus == i)
				ft_putstr(tcap->underline);
			ft_putstr(tcap->data[i]);
			ft_putstr(tcap->reset);
			ft_move(tcap, "right", tcap->max_len - ft_strlen(tcap->data[i]) + 2);
			i++;
		}
	return (1);
}

int		main(int ac, char **av)
{
	t_term	term;
	char	buffer[2];
	char	touche[2];
	t_cap	tcap;

	if (!(tgetent(NULL, getenv("TERM"))) || !init_tcap(&term, &tcap, ac, av))
		return (-1);
	signal(SIGINT, sig_handler);
	print_argv(&tcap);
	while (19)
	{
		ft_bzero(buffer, 2);
		read(0, &buffer, 1);
		if (buffer[0] == 27 || buffer[0] == 59)
		{
			ft_bzero(touche, 2);
			read(0, touche, 2);
			read_arrows(touche, buffer[0] == 59, &tcap);
		}
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d\n");
			return (0);
		}
	}
	return (0);
}
