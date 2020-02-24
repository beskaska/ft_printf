/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:58:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/24 15:09:15 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MAX_PRINTF_ARG 190
# define MAX_LLONG_DIGIT 20
# define CONVERSION_SPECIFIERS "diouxXcspfeg"
# define PRINTF_FLAGS "hlL"

# include <stdarg.h>
# include "libft/libft.h"
# include <stdio.h> //DEL

typedef struct	s_printf
{
	char			*text;
	size_t			text_length;
	size_t			arg_type;
	void			*content;
	int				arg_number;
	char			sign;
	char			space;
	char			zero;
	char			sharp;
	char			left_adjusted;
	int				width_asterisk; //-1 - if not defined; 0 - if defined; >0 - number of an arg 
	int				width;
	int				precision_asterisk; //-1 - if not defined; 0 - if defined; >0 - number of an arg
	int				precision;
	struct s_printf	*next;
}				t_printf;

typedef struct	s_args
{
	t_printf		*usedin;
	struct s_args	*next;
}				t_args;

int				ft_printf(const char *format, ...);
void			ft_printf_parsing(char **format, t_printf *cur, t_args **args, int *max_arg);
void			ft_printf_get_args(t_args **args, va_list ap);
int				ft_printf_print(t_printf *cur);
int				to_signed_dec(unsigned long long n, t_printf *cur, int base);
int				to_unsigned_num(unsigned long long n, t_printf *cur, int base);
int				to_unsigned_hex(unsigned long long n, t_printf *cur, int base);
int				to_csp(t_printf *cur);
int				to_float(t_printf *cur, long double n);

#endif