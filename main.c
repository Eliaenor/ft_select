/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/02 14:50:08 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/02 14:50:10 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			main(int argc, char **argv)
{
	t_data				*data;
	t_data				*first;
	t_info				info;

	if ((info.nbr_of_elem = argc - 1) == 0)
		return (1);
	first = ft_init_display(argv, &info, data);
	ft_init_global(first, &info);
	signal(28, sig_screen);
	signal(18, sig_ctrl_z);
	signal(2, sig_ctrl_c);
	signal(3, sig_ctrl_c);
	if (init_term() == 1)
		return (0);
	if ((data = voir_touche(first, &info)) != NULL)
	{
		ft_reset();
		display_list_select(data);
	}
	else
		ft_reset();
	return (0);
}

char		*get_var_env(char *varenv)
{
	int				len;
	int				i;
	char			*str;
	extern char		**environ;

	i = 0;
	len = ft_strlen(varenv);
	if (!environ[i])
		return (NULL);
	while (environ[i] && ft_strncmp(environ[i], varenv, len) != 0)
		i++;
	str = environ[i];
	return (str + len);
}

int			ft_outc(int c)
{
	write(isatty(1), &c, 1);
	return (0);
}

void		ft_reset(void)
{
	tputs(tgetstr("ho", NULL), 0, ft_outc);
	tputs(tgetstr("te", NULL), 0, ft_outc);
	tputs(tgetstr("ve", NULL), 0, ft_outc);
}

t_data		*voir_touche(t_data *data, t_info *info)
{
	char	buffer[3];

	while (1)
	{
		ft_bzero(buffer, 3);
		display_list(data, info);
		read(0, buffer, 3);
		if (buffer[0] == 27)
		{
			if ((data = ft_escapechar(data, info, buffer)) == NULL)
				return (NULL);
		}
		else if (buffer[0] == 32 || buffer[0] == 127 || buffer[0] == 126)
		{
			if ((data = ft_delorspace(data, buffer)) == NULL)
				return (NULL);
		}
		else if (buffer[0] == 10)
		{
			while (data->first != 1)
				data = data->next;
			return (data);
		}
	}
	return (NULL);
}
