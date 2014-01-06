/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 00:02:52 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/03 00:02:54 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_data		*ft_up_arrow(t_data *data)
{
	tputs(tgetstr("do", NULL), 0, ft_outc);
	tputs(tgetstr("up", NULL), 0, ft_outc);
	ft_putnstr(data->arg, data->len, data->select);
	if (data->first == 1)
	{
		while (data->prev->first != 1)
		{
			tputs(tgetstr("do", NULL), 0, ft_outc);
			data = data->prev;
		}
		data = data->prev;
	}
	else
		tputs(tgetstr("up", NULL), 0, ft_outc);
	data = data->prev;
	tputs(tgetstr("do", NULL), 0, ft_outc);
	tputs(tgetstr("up", NULL), 0, ft_outc);
	ft_underline(data);
	return (data);
}

t_data		*ft_down_arrow(t_data *data)
{
	char	*res;

	tputs(tgetstr("do", NULL), 0, ft_outc);
	tputs(tgetstr("up", NULL), 0, ft_outc);
	ft_putnstr(data->arg, data->len, data->select);
	if (data->next->first == 1)
		res = tgetstr("ho", NULL);
	else
		res = tgetstr("do", NULL);
	tputs(res, 0, ft_outc);
	data = data->next;
	ft_underline(data);
	return (data);
}

t_data		*ft_left_arrow(t_data *data)
{
	int		len;

	len = 0;
	if (data->first == 1)
		data = to_the_last(data);
	else
	{
		len = ft_strlen(data->prev->arg);
		while (len + 1 != 0)
		{
			tputs(tgetstr("le", NULL), 0, ft_outc);
			len--;
		}
		data = data->prev;
	}
	return (data);
}

t_data		*to_the_last(t_data *data)
{
	while (data->next->first != 1)
		tputs(tgetstr("do", NULL), 0, ft_outc);
	return (data);
}

t_data		*ft_space(t_data *data)
{
	int		len;

	len = 0;
	if (data->select == 0)
	{
		tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
		tputs(tgetstr("do", NULL), 0, ft_outc);
		tputs(tgetstr("up", NULL), 0, ft_outc);
		ft_putnstr(data->arg, data->len, data->select);
		data->select = 1;
		tputs(tgetstr("me", NULL), 0, ft_outc);
	}
	else
	{
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
		tputs(tgetstr("do", NULL), 0, ft_outc);
		tputs(tgetstr("up", NULL), 0, ft_outc);
		ft_putstr_fd(data->arg, isatty(1));
		data->select = 0;
	}
	if (data->next->first == 1)
		tputs(tgetstr("ho", NULL), 0, ft_outc);
	else
		tputs(tgetstr("do", NULL), 0, ft_outc);
	data = data->next;
	ft_underline(data);
	return (data);
}

t_data		*ft_delete(t_data *data, t_data *next)
{
	if (data->first == 1)
		data->next->first = 1;
	data->prev->next = data->next;
	data->next->prev = data->prev;
	if (data == data->next)
	{
		ft_free(data);
		return (NULL);
	}
	else
	{
		ft_free(data);
		return (next);
	}
}

void		ft_underline(t_data *data)
{
	tputs(tgetstr("us", NULL), 0, ft_outc);
	if (data->select == 1)
		tputs(tgetstr("mr", NULL), 0, ft_outc);
	ft_putnstr(data->arg, data->len, data->select);
	tputs(tgetstr("ue", NULL), 0, ft_outc);
	tputs(tgetstr("me", NULL), 0, ft_outc);
}

void		ft_free(t_data *data)
{
	free(data->arg);
	free(data);
}
