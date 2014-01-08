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

int			display_list(t_data *data, t_info *info)
{
	int		i;

	i = 0;
	tputs(tgetstr("dl", NULL), 1, ft_outc);
	tputs(tgetstr("ho", NULL), 0, ft_outc); // cursor to home
	while (data->next->first != 1)
	{
		ft_putarg(data, i, info->lenmax);
		i++;
		data = data->next;
	}
	if (data->next->first == 1)
		ft_putarg(data, i, info->lenmax);
	tputs(tgetstr("ho", NULL), 0, ft_outc);
	data = data->next;
	ft_underline(data);
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

int			ft_putarg(t_data *data, int num, int lenmax)
{
	int		line;
	int		col;
	int		tmp;

	tmp = 0;
	line = tgetnum("li");
	col = (num / line);
	tmp = col * (lenmax + 2);
	while (tmp != 0)
	{
		tputs(tgetstr("nd", NULL), 0, ft_outc);
		tmp--;
	}
	if (data->select == 1)
	{
		tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
		ft_putstr_fd(data->arg, isatty(1));
	}
	else
	{
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
		ft_putstr_fd(data->arg, isatty(1));
	}
	tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
	if ((num + 1) % line == 0)
		tputs(tgetstr("ho", NULL), 0, ft_outc);
	else
		tputs(tgetstr("do", NULL), 0, ft_outc);
	return (0);
}

