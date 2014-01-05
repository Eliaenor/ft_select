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

char	*ft_dupandfill(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char*)malloc(sizeof(char) * (len + 1));
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= len)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


void	ft_putnstr(char *str, int n)
{
	int		i;

	i = 0;
	while (i <= n)
	{
		write(1, &str[i], 1);
		i++;
	}
}
