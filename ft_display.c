/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 12:31:43 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/05 12:31:45 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			display_list(t_data *data)
{
	tputs(tgetstr("dl", NULL), 1, ft_outc);
	tputs(tgetstr("ho", NULL), 0, ft_outc); // cursor to home
	ft_underline(data);
	ft_putstr_fd("\n", isatty(1));
	data = data->next;
	while (data->next->first != 1)
	{
		if (data->select == 1)
		{
			tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
			ft_putnstr(data->arg, data->len, data->select);
		}
		else
		{
			tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
			ft_putstr_fd(data->arg, isatty(1));
		}
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
		ft_putstr_fd("\n", isatty(1));
		data = data->next;
	}
	if (data->select == 1)
		tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
	else
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
	ft_putstr_fd(data->arg, isatty(1));
	tputs(tgetstr("ho", NULL), 0, ft_outc);
	return (0);
}

int			display_list_select(t_data *data)
{
	while (data->next->first != 1)
	{
		if (data->select == 1)
		{
			ft_putnstr_out(data->arg, data->len);
			write(1, " ", 1);
		}
		data = data->next;
	}
	if (data->select == 1)
	{
		ft_putnstr_out(data->arg, data->len);
	}
	data = data->next;
	return (0);
}
