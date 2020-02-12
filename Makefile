# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 21:18:08 by aimelda           #+#    #+#              #
#    Updated: 2020/02/11 20:55:44 by aimelda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

HDR		=	ft_printf.h

SRC		=	ft_printf.c			\
			parsing.c			\
			printing.c			\
			diouxX.c			\

OBJ		=	$(addsuffix .o, $(basename $(SRC)))

NEW_OBJ	=	$(addsuffix .o, $(basename $?))

all: $(NAME)

$(NAME): $(SRC)
	make -C libft/
	gcc -g -I$(HDR) -c $?
	ar rc $@ $(NEW_OBJ)
	ranlib $@

clean:
	rm -rf $(OBJ)
	make clean -C libft/

fclean:
	rm -rf $(NAME)
	rm -rf $(OBJ)
	make fclean -C libft/

re: fclean all