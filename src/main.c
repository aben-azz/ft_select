/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/21 16:58:08 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>

t_global	*g_global;

/*
** int			debug(void)
** {
** 	int fd;
**
** 	return (fd = open("log.log", O_RDWR | O_APPEND | O_CREAT, 0666));
** }
*/

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
	ft_putstr_fd("\x1b[31m[\x1b[0m", 2);
	if (tcap->selected[i])
		ft_termcap(tcap->reverse_mode);
	if (tcap->focus == i)
		ft_termcap(tcap->underline);
	ft_putstr_fd(string[i], 2);
	ft_move(tcap, "right", tcap->max_len - ft_strlen(string[i]) + 4);
	ft_termcap(tcap->reset);
	ft_putstr_fd("\x1b[31m]\x1b[0m", 2);
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
	ft_putstr_fd("OPTIONS: \n\
	Backspace/DEL pour supprimer un element de la liste \n\
	Touches flechees pour parcourir la liste \n\
	Espace pour selectionner un element de la liste\x1b[0m\n", 2);
	tcap->row = tcap->xmax / ft_max(tcap->max_len + 4, 1);
	tcap->row = ft_min(tcap->size, tcap->row);
	tcap->column = tcap->size / ft_max(tcap->row, 1);
	tcap->carry = tcap->size % ft_max(tcap->row, 1);
	while (++c < tcap->column && (r = -1))
	{
		while (++r < tcap->row)
			print_file_name(tcap->data, tcap, i++);
		ft_move(tcap, "down", 1);
	}
	while (tcap->carry && tcap->data[i])
		print_file_name(tcap->data, tcap, i++);
	return (1);
}

int		read_buffer(t_cap *tcap)
{
	char buffer[4];

	ft_bzero(buffer, 4);
	ft_termcap(tcap->unset_cursor);
	if (!tcap->size)
	{
		ft_termcap(tparm(tgetstr("cm", NULL), 0, 0));
		ft_termcap(tcap->clr_all_line);
		return (ft_reset());
	}
	read(0, &buffer, 3);
	if (buffer[0] == 27 && buffer[1])
		read_arrows(buffer + 1, tcap);
	else if (!~read_keys(buffer[0], tcap))
		return (ft_reset());
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
		ft_putstr_fd("Erreur, TERM est indéfini", 2);
		return (ft_reset());
	}
	init_signal();
	print_argv(&tcap);
	while ("ft_select")
		if (!read_buffer(&tcap))
			return (0);
	ft_reset();
	return (0);
}
