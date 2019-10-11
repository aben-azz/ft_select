/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/11 15:37:53 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# define ARROW_UP		65
# define ARROW_DOWN		66
# define ARROW_RIGHT	67
# define ARROW_LEFT		68
# define ENTER			10
typedef struct stat	t_stat;
typedef struct termios		t_term;
typedef struct	s_cap
{
	char		*up;
	char		*down;
	char		*right;
	char		*left;
	char		*carriage;
	char		*clr_curr_line;
	char		*clr_all_line;
	char		*sound;
	int			cursx;
	int			cursx_max;
	int			cursy_max;
	int			cursy;
}				t_cap;

void			display_prompt_prefix();
/*
**	SIGNAL_HANDLER.C
*/

void	init_signal(void);

#endif
