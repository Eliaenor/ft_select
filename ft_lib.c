/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 10:50:55 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/05 10:50:57 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_data		*ft_escapechar(t_data *data, t_info *info, char *buffer)
{
	if (buffer[1] == 0)
		return (NULL);
	if (buffer[2] == 65)
		data = ft_up_arrow(data);
	else if (buffer[2] == 66)
		data = ft_down_arrow(data);
	else if (buffer[2] == 67)
		data = ft_right_arrow(data, info);
	else if (buffer[2] == 68)
		data = ft_left_arrow(data, info);
	return (data);
}

t_data		*ft_delorspace(t_data *data, char *buffer)
{
	if (buffer[0] == 32)
		data = ft_space(data);
	else if (buffer[0] == 127 || buffer[0] == 126)
	{
		if ((data = ft_delete(data, data->next)) == NULL)
			return (NULL);
		while (data->first != 1)
			data = data->next;
		data->cursor = 1;
	}
	return (data);
}

t_data		*ft_display_arg(t_data *data, t_info *info)
{
	int		i;

	i = 0;
	while (data->next->first != 1)
	{
		ft_putarg(data, i, info);
		i++;
		data = data->next;
	}
	if (data->next->first == 1)
		ft_putarg(data, i, info);
	return (data);
}

t_data		*ft_reset_display(t_data *data, t_info *info)
{
	int		tmp;

	tmp = 0;
	while (tmp != info->nbr_of_lines)
	{
		tputs(tgetstr("dl", NULL), 1, ft_outc);
		tmp++;
	}
	while (data->first != 1)
		data = data->next;
	tputs(tgetstr("dl", NULL), 1, ft_outc);
	tputs(tgetstr("ho", NULL), 0, ft_outc);
	return (data);
}

int			ft_get_size(t_info *info)
{
	char	*term_name;

	term_name = get_var_env("TERM=");
	if (term_name == NULL)
		return(1);
	tgetent(NULL, term_name);
	info->nbr_of_lines = tgetnum("li");
	info->nbr_of_columns = tgetnum("co");
	return (0);
}
