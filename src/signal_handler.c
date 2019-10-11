/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:36:11 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/11 15:07:14 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Handler for CTRL+C signal in idle status.
*/
static void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		exit(0);
	}
}

/*
** Handler for window resizing signal. (tcaps)
*/
/*
** static void	sigwinch_handler(int sig)
** {
** 	t_cap	*tcap;
** 	int		p;
** 	int		prompt_len;
**
** 	tcap = g_shell->tcap;
** 	p = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
** 	prompt_len = tcap->init_len;
** 	if (sig == SIGWINCH)
** 	{
** 		init_termcap(tcap);
** 		if (prompt_len >= g_shell->tcap->cursx_max + 1)
** 			tcap->prompt_len = prompt_len % (tcap->cursx_max + 1);
** 		else
** 			tcap->prompt_len = prompt_len;
** 		tcap->cursy = (p + tcap->prompt_len) / (tcap->cursx_max + 1);
** 		tcap->cursx = (p + tcap->prompt_len) % (tcap->cursx_max + 1);
** 		if (g_shell->autocomp->state)
** 		{
** 			tputs(tcap->clr_all_line, 1, ft_put_termcaps);
** 			ft_tab(tcap, g_shell->autocomp);
** 		}
** 	}
** }
*/

/*
** Handler for CTRL+Z in idle status.
*/
static void	sigtstp_handler(int sig)
{
	if (sig == SIGTSTP)
	{
		//ft_putchar(7);
		signal(SIGTSTP, sigtstp_handler);
	}
}

void	init_signal(void)
{
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGINT, sigint_handler);
	//signal(SIGWINCH, sigwinch_handler);
}
