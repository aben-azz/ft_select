/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/11 15:41:39 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <unistd.h>

int		init_termcaps(t_term *term)
{
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (0);
	return (1);
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

void read_arrows(char touche[2], int shift)
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
		display_prompt();
	}
	else
	{
		if (touche[1] == ARROW_UP)
			ft_printf("{U}\n");
		else if (touche[1] == ARROW_DOWN)
			ft_printf("{D}\n");
		else if (touche[1] == ARROW_LEFT)
			ft_printf("{L}\n");
		else if (touche[1] == ARROW_RIGHT)
			ft_printf("{R}\n");
		if (touche[1] == ARROW_UP || touche[1] == ARROW_DOWN ||
				touche[1] == ARROW_LEFT || touche[1] == ARROW_RIGHT)
			display_prompt();
	}
}

int		main(int ac, char **av)
{
	t_term	term;
	char	buffer[2];
	char	touche[2];
	(void)ac;
	(void)av;
	if (!(tgetent(NULL, getenv("TERM"))) || !init_termcaps(&term))
		return (-1);
	signal(SIGINT, sig_handler);
	display_prompt();
	while (19)
	{
		ft_bzero(buffer, 2);
		read(0, &buffer, 1);
		if (buffer == 27 || buffer == 59)
		{
			ft_bzero(touche, 2);
			read(0, touche, 2);
			read_arrows(touche, buffer == 59);
		}
		else if (buffer == 4)
		{
			printf("Ctlr+d\n");
			return (0);
		}
		else if (buffer == 10)
		{
			ft_putchar('\n');
			display_prompt();
		}
		else
			ft_printf("%c", buffer);
	}
	return (0);
}
