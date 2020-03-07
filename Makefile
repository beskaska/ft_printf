# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 21:18:08 by aimelda           #+#    #+#              #
#    Updated: 2020/03/07 19:40:18 by aimelda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

HDR		=	ft_printf.h

LIB		=	libft/libft.a

SRC		=	ft_printf.c			\
			parsing.c			\
			get_args.c			\
			printing.c			\
			diouxX.c			\
			csp.c				\
			feg.c				\
			arithmetic.c		\

OBJ		=	$(addsuffix .o, $(basename $(SRC)))

NEW_OBJ	=	$(addsuffix .o, $(basename $?))

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	make -C libft/
	gcc -g -I$(HDR) -c $?
	ar rc $@ $(NEW_OBJ) libft/*.o
	ranlib $@

clean:
	rm -rf $(OBJ)
	make clean -C libft/

fclean:
	rm -rf $(NAME)
	rm -rf $(OBJ)
	make fclean -C libft/

re: fclean all