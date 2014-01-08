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
	char	*term_name;
	int		tmp;

	i = 0;
	term_name = get_var_env("TERM=");
	if (term_name == NULL)
		return(0);
	tgetent(NULL, term_name);
	info->nbr_of_lines = tgetnum("li");
	tmp = 0;
	while (tmp != info->nbr_of_lines)
	{
		tputs(tgetstr("dl", NULL), 1, ft_outc);
		tmp++;
	}
	while (data->first != 1)
		data = data->next;
	tputs(tgetstr("dl", NULL), 1, ft_outc);
	tputs(tgetstr("ho", NULL), 0, ft_outc); // cursor to home
	while (data->next->first != 1)
	{
		ft_putarg(data, i, info);
		i++;
		data = data->next;
	}
	if (data->next->first == 1)
		ft_putarg(data, i, info);
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
	if ((num + 1) % line == 0)
		tputs(tgetstr("ho", NULL), 0, ft_outc);
	else
		tputs(tgetstr("do", NULL), 0, ft_outc);
	return (0);
}

