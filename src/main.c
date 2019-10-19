/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/19 16:43:57 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>

t_global	*g_global;

int			debug(void)
{
	int fd;

	return (fd = open("log.log", O_RDWR | O_APPEND | O_CREAT, 0666));
}

int		return_selected(t_cap *tcap)
{
	int i;
	int is_first;

	is_first = 1;
	i = 0;
	ft_termcap(tparm(tgetstr("cm", NULL), 0, 0));
	ft_termcap(tcap->clr_all_line);
	while (tcap->data[i])
	{
		if (tcap->selected[i])
		{
			if (!is_first)
				ft_putchar(' ');
			else
				is_first = 0;
			ft_putstr(tcap->data[i]);
		}
		i++;
	}
	return (-1);
}

void	print_file_name(char **string, t_cap *tcap, int i)
{
	ft_putchar_fd('[', 2);
	if (tcap->selected[i])
		ft_termcap(tcap->reverse_mode);
	if (tcap->focus == i)
		ft_termcap(tcap->underline);
	ft_putstr_fd(string[i], 2);
	ft_move(tcap, "right", tcap->max_len - ft_strlen(string[i]) + 4);
	ft_termcap(tcap->reset);
	ft_putchar_fd(']', 2);
}

int		print_argv(t_cap *tcap)
{
	int c;
	int r;
	int i;

	i = 0;
	c = -1;
	ft_termcap(tparm(tgetstr("cm", NULL), 0, 0));
	ft_termcap(tcap->clr_all_line);
	tcap->row = tcap->xmax / ft_max(tcap->max_len + 4, 1);
	tcap->row = ft_min(tcap->size, tcap->row);
	tcap->column = tcap->size / ft_max(tcap->row, 1);
	tcap->carry = tcap->size % ft_max(tcap->row, 1);
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
	return (1);
}

int		read_buffer(t_cap *tcap, t_term *term_backup)
{
	char buffer[4];

	ft_bzero(buffer, 4);
	ft_termcap(tcap->unset_cursor);
	if (!tcap->size)
	{
		tcsetattr(0, TCSANOW, term_backup);
		ft_termcap(tcap->set_cursor);
		return (0);
	}
	read(0, &buffer, 3);
	if (buffer[0] == 27 && buffer[1])
		read_arrows(buffer + 1, tcap);
	else if (!~read_keys(buffer[0], tcap))
	{
		ft_termcap(tcap->set_cursor);
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_term	term;
	t_term	term_backup;
	t_cap	tcap;

	if (!(tgetent(NULL, getenv("TERM"))) || !init_tcap(&term, &tcap, ac,
		&term_backup) || !init_tcap_variables(&tcap, av))
	{
		tcsetattr(0, TCSANOW, &term_backup);
		return (1);
	}
	init_signal();
	print_argv(&tcap);
	while ("ft_select")
		if (!read_buffer(&tcap, &term_backup))
			return (0);
	ft_termcap(tcap.set_cursor);
	return (0);
}
