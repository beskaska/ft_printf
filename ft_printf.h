/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:58:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/01/28 21:49:52 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

typedef struct	s_printf
{
	char			*text;
	size_t			text_length;
	size_t			arg_number;
	char			arg_type;
	char			sign;
	char			zero;
	char			sharp;
	char			left_adjusted;
	char			width_asterisk;
	int				width;
	char			precision_asterisk_or_defined;
	int				precision;
	struct s_printf	*next;
}				t_printf;

typedef struct	s_args
{
	t_printf		*usedin;
	void			*content;
}				t_args;

#endif