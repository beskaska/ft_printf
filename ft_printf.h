/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:58:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/09 19:35:09 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MAX_PRINTF_ARG 190
# define MAX_LLONG_DIGIT 20
# define EXPONENT_BIAS 16383
# define MAX_ULLONG 9223372036854775808UL
# define CONVERSION_SPECIFIERS "diouxXcspfeg"
# define PRINTF_FLAGS "hlL"

# include <stdarg.h>
# include "libft/libft.h"

typedef struct	s_printf
{
	size_t			text_length;
	size_t			argt;
	void			*content;
	char			*text;
	char			sign;
	char			zero;
	char			sharp;
	char			left_adjusted;
	char			error;
	int				arg_number;
	int				width_asterisk;
	int				width;
	int				precision_ast;
	int				precision;
	struct s_printf	*next;
}				t_printf;

typedef struct	s_args
{
	t_printf		*usedin;
	struct s_args	*next;
}				t_args;

int				ft_printf(const char *format, ...);
int				ft_printf_pars(char **format, t_printf *cur, t_args **args,
					int res);
int				arg_malloc(t_args **args, t_printf *cur, int res, int *dst);
void			free_args(t_args *to_del);
int				ft_printf_get_args(t_args **args, va_list ap, int i);
int				ft_printf_print(t_printf *cur);
int				to_signed_dec(t_printf *cur, char base);
int				to_unsigned_num(t_printf *cur, char base);
int				to_unsigned_hex(t_printf *cur, unsigned long long n, char base);
int				to_csp(t_printf *cur);
int				to_float(t_printf *cur);
char			*ft_printf_multiply(char *num, int *len, int exp);
char			*ft_printf_divide(char *num, int *len, int exp, int precision);
int				free_all(t_args **args);

#endif
