/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 12:36:16 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/05 12:36:17 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_data		*ft_init(char *arg, t_data *prev, t_data *first, t_info *info)
{
	t_data	*newdata;

	newdata = (t_data*)malloc(sizeof(t_data));
	newdata->next = (t_data*)malloc(sizeof(t_data*));
	newdata->prev = (t_data*)malloc(sizeof(t_data*));
	newdata->arg = ft_dupandfill(arg, info->lenmax);
	newdata->len = ft_strlen(arg) - 1;
	newdata->select = 0;
	newdata->first = 0;
	newdata->next = first;
	prev->next = newdata;
	first->prev = newdata;
	newdata->prev = prev;
	return(newdata);
}

t_data		*ft_init_first(char *arg, t_info *info)
{
	t_data	*newdata;

	newdata = (t_data*)malloc(sizeof(t_data));
	newdata->next = (t_data*)malloc(sizeof(t_data*));
	newdata->prev = (t_data*)malloc(sizeof(t_data*));
	newdata->arg = ft_dupandfill(arg, info->lenmax);
	newdata->len = ft_strlen(arg) - 1;
	newdata->select = 0;
	newdata->first = 1;
	newdata->next = newdata;
	newdata->prev = newdata;
	return(newdata);
}

t_data		*ft_init_display(char **argv, t_info *info, t_data *data)
{
	int			i;
	int			tmp;
	t_data		*first;

	i = 1;
	info->lenmax = 0;
	while (argv[i])
	{
		tmp = ft_strlen(argv[i]);
		info->lenmax = (tmp > info->lenmax ? tmp : info->lenmax);
		i++;
	}
	i = 1;
	while (argv[i])
	{
		if (i == 1)
		{
			data = ft_init_first(argv[i], info);
			first = data;
		}
		else
			data = ft_init(argv[i], data, first, info);
		i++;
	}
	return (first);
}

