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
#include <curses.h>
#include <term.h>

typedef struct		s_data
{
	char			*arg;
	int				len;
	struct s_data	*next;
	struct s_data	*prev;
	int				first;
	int				select;
}					t_data;

typedef struct		s_info
{
	int				lenmax;
	int				nbr_of_elem;
	int				nbr_of_lines;
	int				nbr_of_columns;
	int				first;
}					t_info;

char		*get_var_env(char *varenv);
int			voir_touche(t_data *data);
t_data		*ft_init_display(char **argv, t_info *info, t_data *data);
t_data		*ft_init(char *arg, t_data *prev, t_data *first, t_info *info);
t_data		*ft_init_first(char *arg, t_info *info);
int			display_list(t_data *data);
int			ft_outc(int c);
t_data		*ft_right_arrow(t_data *data);
t_data		*ft_left_arrow(t_data *data);
t_data		*ft_down_arrow(t_data *data);
t_data		*ft_up_arrow(t_data *data);
t_data		*ft_space(t_data *data);
t_data		*to_the_last(t_data *data);
t_data		*ft_delete(t_data *data, t_data *next);
void		ft_free(t_data *data);
int			display_list_select(t_data *data);
char		*ft_dupandfill(char *src, int len);
void		ft_putnstr(char *str, int n);

#endif
