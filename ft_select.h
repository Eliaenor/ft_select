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
#include <signal.h>

typedef struct		s_data
{
	char			*arg;
	int				first;
	int				select;
	int				cursor;
	struct s_data	*next;
	struct s_data	*prev;
}					t_data;

typedef struct		s_info
{
	int				lenmax;
	int				nbr_of_elem;
	int				nbr_of_lines;
	int				nbr_of_columns;
}					t_info;


char		*get_var_env(char *varenv);
int			init_term(void);
int			ft_get_size(t_info *info);
int			ft_cursor_select(t_data *data);
int			display_list(t_data *data, t_info *info);
int			ft_outc(int c);
int			display_list_select(t_data *data);
int			ft_putarg(t_data *data, int num, t_info *info);
int			ft_init_global(t_data *data, t_info *info);
void		ft_putnstr(char *str, int n, int select);
void		ft_putnstr_out(char *str, int n);
void		ft_reset();
void		sig_ctrl_c(int n);
void		sig_ctrl_z(int n);
void		sig_screen(int n);
void		sig_fg(int n);
t_data		*ft_right_arrow(t_data *data, t_info *info);
t_data		*ft_left_arrow(t_data *data, t_info *info);
t_data		*ft_up_arrow(t_data *data);
t_data		*ft_down_arrow(t_data *data);
t_data		*ft_space(t_data *data);
t_data		*ft_delete(t_data *data, t_data *next);
t_data		*voir_touche(t_data *data, t_info *info);
t_data		*ft_init_display(char **argv, t_info *info, t_data *data);
t_data		*ft_init(char *arg, t_data *prev, t_data *first, t_info *info);
t_data		*ft_init_first(char *arg, t_info *info);
t_data		*ft_reset_display(t_data *data, t_info *info);
t_data		*ft_display_arg(t_data *data, t_info *info);
t_data		*ft_escapechar(t_data *data, t_info *info, char *buffer);
t_data		*ft_delorspace(t_data *data, char *buffer);

#endif
