/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/14 02:18:34 by aben-azz         ###   ########.fr       */
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
	char		*reset;
	char		*underline;
	char		*reverse_mode;
	int			xmax;
	int			ymax;
	int			selected;
	int			focus;
	int			*ignored;
	int			size;
	char		**data;
	int			max_len;
	int			column;
	int			row;
	int			carry;
}				t_cap;
typedef struct	s_global
{
	t_term	*term;
	t_term	*term_backup;
	t_cap	*tcap;
}				t_global;
extern	t_global *g_global;
/*
**	SIGNAL_HANDLER.C
*/

void	init_signal(void);
int		print_argv(t_cap *tcap);
int		arrow_up_event(t_cap *tcap);
int		arrow_down_event(t_cap *tcap);
int		arrow_right_event(t_cap *tcap);
int		arrow_left_event(t_cap *tcap);
#endif
