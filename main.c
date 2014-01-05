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
	t_data				*data;
	t_data				*first;
	t_info				info;

	info.nbr_of_elem = argc - 1;
	first = ft_init_display(argv, &info, data);
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
	if ((data = voir_touche(first)) != NULL)
	{
		while (argc >= 3)
		{
			tputs(tgetstr("sr", NULL), 1, ft_outc);
			argc--;
		}
		display_list_select(data);
	}
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

t_data		*voir_touche(t_data *data)
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
			return (data);
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
	return (NULL);
}
