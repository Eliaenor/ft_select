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

t_data		*ft_init_data(int f, char *arg, t_data *previous, t_data *first)
{
	t_data	*newdata;

	newdata = (t_data*)malloc(sizeof(t_data));
	newdata->next = (t_data*)malloc(sizeof(t_data*));
	newdata->prev = (t_data*)malloc(sizeof(t_data*));
	newdata->arg = ft_strdup(arg);
	newdata->select = 0;
	if (f == 1)
	{
		newdata->first = 1;
		newdata->next = newdata;
		newdata->prev = newdata;
	}
	else
	{
		newdata->first = 0;
		newdata->next = first;
		previous->next = newdata;
		first->prev = newdata;
		newdata->prev = previous;
	}
	return(newdata);
}

t_data		*ft_right_arrow(t_data *data)
{
	char	*res;
	int		len;

	len = 0;
	if (data->next->first == 1)
		res = tgetstr("ho", NULL);
	else
		res = tgetstr("nd", NULL);
	len = ft_strlen(data->arg);
	while (len + 1 != 0)
	{
		tputs(res, 0, ft_outc);
		len--;
	}
	data = data->next;
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
	int		len;

	len = 0;
	while (data->next->first != 1)
	{
		len += ft_strlen(data->arg) + 1;
		data = data->next;
	}
	while (len != 0)
	{
		tputs(tgetstr("nd", NULL), 0, ft_outc);
		len--;
	}
	return (data);
}

t_data		*ft_space(t_data *data)
{
	int		len;

	len = 0;
	if (data->select == 0)
	{
		tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
		data->select = 1;
	}
	else
	{
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
		data->select = 0;
	}
	ft_putstr(data->arg);
	if (data->next->first == 1)
		tputs(tgetstr("ho", NULL), 0, ft_outc);
	else
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	data = data->next;
	return (data);
}

t_data		*ft_delete(t_data *data)
{
	t_data	*next;

	if (data->first == 1)
		data->next->first = 1;
	data->prev->next = data->next;
	data->next->prev = data->prev;
	next = data->next;
	ft_free(data);
	return (next);
}

void		ft_free(t_data *data)
{
	free(data->arg);
	free(data->next);
	free(data->prev);
	free(data);
}
