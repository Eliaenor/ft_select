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

int main(int argc, char **argv)
{
	char				*term_name;
	struct termios		term;
	int					i;
	t_data				*data;
	t_data				*first;

	(void)argc;
	i = 1;
	while (argv[i])
	{
		data = ft_init_data(i, argv[i], data, first);
		if (i == 1)
			first = data;
		i++;
	}
	term_name = get_var_env("TERM=");
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);// On applique les changements
	tputs(tgetstr("cl", NULL), 0, ft_outc); //clear term
	display_list(first);
	voir_touche(first);
	return (0);
}

int			display_list(t_data *data)
{
	tputs(tgetstr("dl", NULL), 1, ft_outc);
	tputs(tgetstr("ho", NULL), 0, ft_outc); // cursor to home

	while (data->next->first != 1)
	{
		if (data->select == 1)
			tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
		else
			tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
		ft_putstr(data->arg);
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
		ft_putstr("\n");
		data = data->next;
	}
	if (data->select == 1)
		tputs(tgetstr("mr", NULL), 0, ft_outc); // inverse video output
	else
		tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
	ft_putstr(data->arg);
	tputs(tgetstr("ho", NULL), 0, ft_outc);
	return (0);
}

int			display_list_select(t_data *data)
{
	while (data->next->first != 1)
	{
		if (data->select == 1)
		{
			tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
			ft_putstr(data->arg);
			ft_putstr(" ");
		}
		data = data->next;
	}
	if (data->select == 1)
		{
			tputs(tgetstr("me", NULL), 0, ft_outc); // reset video output
			ft_putstr(data->arg);
		}
		data = data->next;
	ft_putstr("\n");
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
	while (environ[i] && ft_strncmp(environ[i], varenv, len) != 0)
		i++;
	str = environ[i];
	return (str + len);
}

int		ft_outc(int c)
{
	ft_putchar(c);
	return (0);
}

int		voir_touche(t_data *data)
{
	char	buffer[3];
	int		len;

	while (1)
	{
		len = 0;
		read(0, buffer, 3);
		if (buffer[0] == 27)
		{
			if (buffer[2] == 65) // if fleche droite
				data = ft_up_arrow(data);
			else if (buffer[2] == 66) // if touche fleche gauche
				data = ft_down_arrow(data);
			/*else if (buffer[2] == 67) // if touche fleche gauche
				data = ft_right_arrow(data);
			else if (buffer[2] == 68) // if touche fleche gauche
				data = ft_left_arrow(data);*/
		}
		else if (buffer[0] == 32) // if touche Espace
			data = ft_space(data);
		else if (buffer[0] == 127)
		{
			data = ft_delete(data, data->next);
			while (data->first != 1)
			{
				data = data->next;
			}
			display_list(data);
		}
		else if (buffer[0] == 10)
		{
			while (data->first != 1)
			{
				data = data->next;
			}
			ft_putstr("\n");
			display_list_select(data);
			return (1);
		}
		else if (buffer[0] == 4)
			tputs(tgetstr("cl", NULL), 0, ft_outc);
		else
		{
			ft_putnbr(buffer[0]);
			ft_putnbr(buffer[1]);
			ft_putnbr(buffer[2]);
		}
	}
	return (0);
}
