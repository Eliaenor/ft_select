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
	int		nbr_columns;

	if (ft_get_size(info) == 1)
		return (0);
	data = ft_reset_display(data, info);
	nbr_columns = (info->nbr_of_elem / info->nbr_of_lines) + 1;
	if ((2 + info->lenmax) * nbr_columns > info->nbr_of_columns)
	{
		ft_putstr_fd("Terminal too small to display the full list", isatty(1));
		tputs(tgetstr("ho", NULL), 0, ft_outc);
		return (1);
	}
	data = ft_display_arg(data, info);
	tputs(tgetstr("ho", NULL), 0, ft_outc);
	data = data->next;
	return (0);
}

int			display_list_select(t_data *data)
{
	while (data->next->first != 1)
	{
		if (data->select == 1)
		{
			ft_putstr(data->arg);
			write(1, " ", 1);
		}
		data = data->next;
	}
	if (data->select == 1)
	{
		ft_putstr(data->arg);
	}
	data = data->next;
	return (0);
}

int			ft_putarg(t_data *data, int num, t_info *info)
{
	int		line;
	int		col;
	int		tmp;

	tmp = 0;
	line = info->nbr_of_lines;
	col = (num / line);
	tmp = col * (info->lenmax + 2);
	while (tmp != 0)
	{
		tputs(tgetstr("nd", NULL), 0, ft_outc);
		tmp--;
	}
	ft_cursor_select(data);
	if ((num + 1) % line == 0)
		tputs(tgetstr("ho", NULL), 0, ft_outc);
	else
		tputs(tgetstr("do", NULL), 0, ft_outc);
	return (0);
}

int			ft_cursor_select(t_data *data)
{
	if (data->cursor == 1)
		tputs(tgetstr("us", NULL), 0, ft_outc);
	if (data->select == 1)
	{
		tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
		ft_putstr_fd(data->arg, isatty(1));
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
	}
	else
		ft_putstr_fd(data->arg, isatty(1));
	tputs(tgetstr("ue", NULL), 0, ft_outc);
	tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
	return (0);
}
