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

	(void)info;
	newdata = (t_data*)malloc(sizeof(t_data));
	newdata->next = (t_data*)malloc(sizeof(t_data*));
	newdata->prev = (t_data*)malloc(sizeof(t_data*));
	newdata->arg = ft_strdup(arg);
	newdata->select = 0;
	newdata->cursor = 0;
	newdata->first = 0;
	newdata->next = first;
	prev->next = newdata;
	first->prev = newdata;
	newdata->prev = prev;
	return (newdata);
}

t_data		*ft_init_first(char *arg, t_info *info)
{
	t_data	*newdata;

	(void)info;
	newdata = (t_data*)malloc(sizeof(t_data));
	newdata->next = (t_data*)malloc(sizeof(t_data*));
	newdata->prev = (t_data*)malloc(sizeof(t_data*));
	newdata->arg = ft_strdup(arg);
	newdata->select = 0;
	newdata->cursor = 1;
	newdata->first = 1;
	newdata->next = newdata;
	newdata->prev = newdata;
	return (newdata);
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
	i = 0;
	while (argv[++i])
	{
		if (i == 1)
		{
			data = ft_init_first(argv[i], info);
			first = data;
		}
		else
			data = ft_init(argv[i], data, first, info);
	}
	return (first);
}

int			init_term(void)
{
	char				*term_name;
	struct termios		term;

	term_name = get_var_env("TERM=");
	if (term_name == NULL)
		return (1);
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	tputs(tgetstr("ti", NULL), 0, ft_outc);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag |= (ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	tputs(tgetstr("vi", NULL), 0, ft_outc);
	return (0);
}

int			reset_term(struct termios *term)
{
	char				*term_name;

	term_name = get_var_env("TERM=");
	if (term_name == NULL)
		return (1);
	tgetent(NULL, term_name);
	tcgetattr(0, term);
	tputs(tgetstr("te", NULL), 0, ft_outc);
	term->c_lflag |= (ICANON);
	term->c_lflag |= (ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, term);
	tputs(tgetstr("ve", NULL), 0, ft_outc);
	return (0);
}

