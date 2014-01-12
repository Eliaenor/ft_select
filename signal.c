/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/11 03:11:54 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/11 03:11:55 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <sys/ioctl.h>

t_data		*data_signal;
t_info		*info_signal;

int			ft_init_global(t_data *data, t_info *info)
{
	data_signal = data;
	info_signal = info;
	return (0);
}

void		sig_screen(int n)
{
	(void)n;
	signal(28, &sig_screen);
	display_list(data_signal, info_signal);
}

void		sig_ctrl_c(int n)
{
	(void)n;
	tputs(tgetstr("te", NULL), 0, ft_outc);
	tputs(tgetstr("ve", NULL), 0, ft_outc);
	exit(0);
}

void		sig_ctrl_z(int n)
{
	struct termios		term;
	char				cp[2];

	(void)n;
	if (isatty(1))
	{
		ft_putstr("Stopping...\n");
		signal(19, sig_fg);
		reset_term(&term);
		cp[0] = term.c_cc[VSUSP];
		cp[1] = 0;
		signal(18, SIG_DFL);
		ioctl(0, TIOCSTI, cp);
	}
}

void		sig_fg(int n)
{
	(void)n;
	signal(19, sig_fg);
	signal(18, sig_ctrl_z);
	init_term();
	display_list(data_signal, info_signal);
}
