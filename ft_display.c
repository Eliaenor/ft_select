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
	while (data->next->first != 1)
	{
		if (data->select == 1)
		{
			tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
			ft_putnstr(data->arg, data->len);
		}
		else
		{
			tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
			ft_putstr(data->arg);
		}
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
		ft_putstr("\n");
		data = data->next;
	}
	if (data->select == 1)
		tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
	else
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
	ft_putstr(data->arg);
	tputs(tgetstr("ho", NULL), 0, ft_outc);
	return (0);
}

int			display_list_select(t_data *data)
{
	while (data->next->first != 1)
	{
		if (data->select == 1)
		{
			tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
			ft_putnstr(data->arg, data->len);
			ft_putstr(" ");
		}
		data = data->next;
	}
	if (data->select == 1)
		{
			tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
			ft_putnstr(data->arg, data->len);
		}
		data = data->next;
	ft_putstr("\n");
	return (0);
}
