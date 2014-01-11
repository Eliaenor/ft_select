/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/11 03:10:46 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/11 03:10:47 by vcourtin         ###   ########.fr       */
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
