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

void	ft_putnstr(char *str, int n, int select)
{
	int		i;

	i = 0;
	if (select == 1)
		tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
	while (i <= n)
	{
		write(isatty(1), &str[i], 1);
		i++;
	}
	tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
}

void	ft_putnstr_out(char *str, int n)
{
	int		i;

	i = 0;
	while (i <= n)
	{
		write(1, &str[i], 1);
		i++;
	}
}
