/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:26:23 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 19:02:59 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		arg_or_width(char **str, t_printf *cur, t_args **args)
{
	int		res;

	res = 0;
	while (ft_isdigit(**str))
		res = res * 10 + *((*str)++) - '0';
	if (res && **str == '$')
		return (arg_malloc(args, cur, res, &cur->arg_number));
	else
	{
		cur->width = res;
		cur->width_asterisk = 0;
		(*str)--;
		return (0);
	}
}

static int		get_precision(char **str, t_printf *p, t_args **args, char c)
{
	int		res;

	res = 0;
	if (!ft_isdigit(*(++(*str))))
		c = *((*str)++);
	while (ft_isdigit(**str))
		res = res * 10 + *((*str)++) - '0';
	if (c == '*')
		if (res && **str == '$')
			return (arg_malloc(args, p, res, &p->precision_ast));
		else
		{
			--(*str);
			p->precision = res;
			return (arg_malloc(args, p, p->arg_number++, &p->precision_ast));
		}
	else
	{
		p->precision_ast = 0;
		p->precision = res * (c != '-');
		if (c && c != '-')
			--(*str);
		--(*str);
	}
	return (0);
}

static int		get_width(char **str, t_printf *cur, t_args **args)
{
	int		res;
	char	*tmp;

	res = 0;
	tmp = *str;
	while (ft_isdigit(*(++(*str))))
		res = res * 10 + **str - '0';
	if (res && **str == '$')
		return (arg_malloc(args, cur, res, &cur->width_asterisk));
	else
	{
		if (tmp != --(*str))
		{
			if (!res)
				cur->zero = '0';
			else
				cur->width = res;
		}
		return (arg_malloc(args, cur, ++(cur->arg_number), &cur->width_asterisk));
	}
}

static int		sasha1(char **format, t_printf *cur, t_args **args)
{
	if (cur->left_adjusted)
		cur->zero = ' ';
	while (ft_strchr(PRINTF_FLAGS, **format))
		cur->argt *= *((*format)++);
	if (ft_strchr(CONVERSION_SPECIFIERS, **format))
	{
		cur->argt *= **format;
		if (!args[cur->arg_number])
			if (arg_malloc(args, cur, cur->arg_number, &cur->arg_number) == -1)
				return (-1);
		if (**format == 'p')
		{
			cur->argt = 'l' * 'l' * 'x';
			cur->sharp = -1;
		}
	}
	else if (**format == '%')
		cur->content = (void*)'%';
	else
		--(*format);
	return (0);
}

int				ft_printf_pars(char **format, t_printf *cur, t_args **args,
					int res)
{
	while (++(*format) && res != -1)
		if (**format >= '1' && **format <= '9')
			res = arg_or_width(format, cur, args);
		else if (**format == '+')
			cur->sign = '+';
		else if (**format == ' ')
		{
			if (!cur->sign)
				cur->sign = ' ';
		}
		else if (**format == '0')
			cur->zero = '0';
		else if (**format == '#')
			cur->sharp = 1;
		else if (**format == '-')
			cur->left_adjusted = 1;
		else if (**format == '.')
			res = get_precision(format, cur, args, 0);
		else if (**format == '*')
			res = get_width(format, cur, args);
		else
			break ;
	if (res != -1)
		return (sasha1(format, cur, args));
	return (0);
}
