/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/14 04:52:24 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>

t_global	*g_global;

int		ft_termcap(int c)
{
	return (write(1, &c, 1));
}

int			debug(void)
{
	int fd;

	return (fd = open("log.log", O_RDWR | O_APPEND | O_CREAT, 0666));
}

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
	if (!(tcap->selected = ft_memalloc(sizeof(int ) * (tcap->size))))
		return (0);
	if (!(tcap->data = ft_splitdup(++argv)))
		return (0);
	while (++i < tcap->size)
		tcap->selected[i] = 0;
	tcap->max_len = 0;
	tcap->focus = 0;
	tcap->selected[0] = 1;
	i = -1;
	while (tcap->data[++i])
		tcap->max_len = ft_max(ft_strlen(tcap->data[i]), tcap->max_len);
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
	if (!~tcsetattr(0, TCSANOW, term) || !(w = ft_memalloc(sizeof(*w))))
		return (0);
	i = ioctl(1, TIOCGWINSZ, w);
	tcap->xmax = (!i ? tgetnum("co") : w->ws_col) - 1;
	tcap->ymax = (!i ? tgetnum("li") : w->ws_row) - 1;
	tcap->size = argc - 1;
	free(w);
	return (1);
}

static void		free_tab_i(char **strings, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(strings[i++]);
	free(strings);
}

void	remove_data(t_cap *tcap, int exception)
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

int		return_selected(t_cap *tcap)
{
	int i;

	i = 0;
	tputs(tparm(tgetstr("cm", NULL), 0, 0), 1, ft_termcap);
	tputs(tcap->clr_all_line, 1, ft_termcap);
	//tputs(tparm(tgetstr("cl", NULL), 0, 0), 1, ft_termcap);
	while (tcap->data[i])
	{
		if (tcap->selected[i])
			ft_printf("%s ", tcap->data[i]);
		i++;
	}
	return (-1);
}

int		read_keys(char touche, t_cap *tcap)
{
	if (touche == 4 || touche == ESC)
		return (-1);
	else if (touche == ENTER)
		return (return_selected(tcap));
	else if (touche == SPACE)
		tcap->selected[tcap->focus] = !tcap->selected[tcap->focus];
	else if (touche == DEL)
		remove_data(tcap, tcap->focus);
	print_argv(tcap);
	return (1);
}

void	read_arrows(char touche[2], t_cap *tcap)
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
			tputs(tcap->down, 1, ft_termcap);
		else if (!ft_strcmp(string, "left"))
			tputs(tcap->left, 1, ft_termcap);
		else if (!ft_strcmp(string, "right"))
			tputs(tcap->right, 1, ft_termcap);
		else if (!ft_strcmp(string, "up"))
			tputs(tcap->up, 1, ft_termcap);
	}
	return (1);
}

void	print_file_name(char **string, t_cap *tcap, int i)
{
	if (tcap->selected[i])
		tputs(tcap->reverse_mode, 1, ft_termcap);
	if (tcap->focus == i)
		tputs(tcap->underline, 1, ft_termcap);
	ft_putstr_fd(string[i], 0);
	tputs(tcap->reset, 1, ft_termcap);
	ft_move(tcap, "right", tcap->max_len - ft_strlen(string[i]) + 2);
}

int	print_argv(t_cap *tcap)
{
	int c;
	int r;
	int i;

	i = 0;
	c = -1;
	tputs(tparm(tgetstr("cm", NULL), 0, 0), 1, ft_termcap);
	tputs(tcap->clr_all_line, 1, ft_termcap);
	tcap->row = tcap->xmax / ft_max(tcap->max_len + 2, 1);
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

int		main(int ac, char **av)
{
	t_term	term;
	t_term	term_backup;
	char	buffer[4];
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
	{
		if (!tcap.size)
		{
			tcsetattr(0, TCSANOW, &term_backup);
			return (0);
		}
		read(0, &buffer, 3);
		if (buffer[0] == 27)
			read_arrows(buffer + 1, &tcap);
		else if (!~read_keys(buffer[0], &tcap))
		{
			dprintf(debug(), "on sort\n");
			return (0);
		}
	}
	return (0);
}
