/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:58:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/08 21:52:19 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MAX_PRINTF_ARG 190
# define CONVERSION_SPECIFIERS "diouxXcspfeg"
# define PRINTF_FLAGS "hlL"

# include <stdarg.h>
# include "libft/libft.h"

typedef struct	s_printf
{
	char			*text;
	size_t			text_length;
	size_t			arg_number;
	size_t			arg_type;
	char			sign;
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
	size_t			arg_type;
	struct s_args	*next;
}				t_args;

void			ft_printf_parsing(char **format, t_printf *cur, t_args **args);
int				ft_printf_print(t_printf *cur, t_args **args, va_list ap);

#endif