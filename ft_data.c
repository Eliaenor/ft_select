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
	data->cursor = 0;
	data = data->prev;
	data->cursor = 1;
	return (data);
}

t_data		*ft_down_arrow(t_data *data)
{
	data->cursor = 0;
	data = data->next;
	data->cursor = 1;
	return (data);
}

t_data		*ft_right_arrow(t_data *data, t_info *info)
{
	int		tmp;

	tmp = info->nbr_of_lines;
	data->cursor = 0;
	while (tmp-- && data->next->first != 1)
		data = data->next;
	if (data->next->first == 1 && tmp != -1)
		data = data->next;
	data->cursor = 1;
	return (data);
}

t_data		*ft_left_arrow(t_data *data, t_info *info)
{
	int		tmp;

	tmp = info->nbr_of_lines;
	data->cursor = 0;
	while (tmp-- && data->first != 1)
		data = data->prev;
	if (data->first == 1 && tmp != -1)
		data = data->prev;
	data->cursor = 1;
	return (data);
}

t_data		*ft_space(t_data *data)
{
	if (data->select == 0)
		data->select = 1;
	else
		data->select = 0;
	data = ft_down_arrow(data);
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
		free(data->arg);
		free(data);
		return (NULL);
	}
	else
	{
		free(data->arg);
		free(data);
		return (next);
	}
}
