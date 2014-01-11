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
/*
void		sig_ctrl_z(int n)
{
	char				*term_name;
	struct termios		term;

	(void)n;
	signal(18, sig_ctrl_z);
	signal(19, sig_fg);
	term_name = get_var_env("TERM=");
	if (term_name == NULL)
		return;
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	tputs(tgetstr("te", NULL), 0, ft_outc);
	term.c_lflag |= (ICANON);
	term.c_lflag |= (ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	tputs(tgetstr("ve", NULL), 0, ft_outc);
}

void		sig_fg(int n)
{
	(void)n;
	signal(19, sig_fg);
	display_list(data_signal, info_signal);
}
*/
