# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcourtin <vcourtin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/02 14:49:57 by vcourtin          #+#    #+#              #
#    Updated: 2014/01/02 14:50:01 by vcourtin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

SRC_C = main.c ft_data.c

LIB_A = libft.a

FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@cd libft; make re
	gcc -g -ltermcap -o $(NAME) $(FLAG) $(SRC_C) $(LIB_A)

clean:
	@cd libft; make clean
	@/bin/rm -f $(LIB_A)

fclean: clean
	@cd libft; make fclean
	@/bin/rm -f $(NAME)

re: fclean all

