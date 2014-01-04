/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/02 14:50:25 by vcourtin          #+#    #+#             */
/*   Updated: 2014/01/02 14:50:26 by vcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

#include "./libft/includes/libft.h"
#include "termcap.h"
#include <curses.h>
#include <term.h>

typedef struct		s_data
{
	char			*arg;
	struct s_data	*next;
	struct s_data	*prev;
	int				first;
	int			select;
}					t_data;

char		*get_var_env(char *varenv);
int			voir_touche(t_data *data);
t_data		*ft_init_data(int f, char *arg, t_data *previous, t_data *first);
int			display_list(t_data *data);
int			ft_outc(int c);
t_data		*ft_right_arrow(t_data *data);
t_data		*ft_left_arrow(t_data *data);
t_data		*ft_space(t_data *data);
t_data		*to_the_last(t_data *data);
t_data		*ft_delete(t_data *data);
void		ft_free(t_data *data);

#endif
