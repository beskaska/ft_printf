/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:34:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/09 19:19:58 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*num_to_txt(unsigned long long n, int exp, int *len)
{
	int		nb;
	char	*txt;

	*len = MAX_LLONG_DIGIT;
	if (n < 10000000000000000000UL)
		--(*len);
	if (!(txt = (char*)malloc(*len + ft_abs(exp) + 1)))
		return (NULL);
	if (exp > 0)
		nb = *len + ft_abs(exp);
	else
		nb = *len;
	txt[nb--] = '\0';
	while (n)
	{
		txt[nb--] = n % 10 + '0';
		n = n / 10;
	}
	return (txt);
}

static char	*get_number(t_printf *cur, char *txt, int *exp, int *len)
{
	*len = 1;
	if ((*exp = *(short*)(txt + 8)) < 0)
		*exp = (short)*exp ^ (short)-32768;
	if (*exp == 32767)
	{
		*len = 3;
		*exp = 0;
		if (*(unsigned long long*)(txt) == MAX_ULLONG)
			txt = ft_strdup("inf");
		else
		{
			txt = ft_strdup("nan");
			cur->sign = 0;
		}
		cur->zero = ' ';
		cur->sharp = 0;
		cur->precision = 0;
		return (txt);
	}
	else if (!*exp && !(*(unsigned long long*)(txt)))
		return (txt = ft_strdup("0"));
	else
		*exp = *exp - EXPONENT_BIAS - (sizeof(long long) * 8 - 1);
	return (num_to_txt(*(unsigned long long*)(txt), *exp, len));
}

static void	put_float(t_printf *cur, char *txt, int len)
{
	if (len > 0)
	{
		while (len && *txt)
		{
			len--;
			ft_putchar(*txt++);
		}
		while (len--)
			ft_putchar('0');
		len++;
	}
	else
		ft_putchar('0');
	if (cur->precision || cur->sharp)
		ft_putchar('.');
	while (cur->precision && *txt)
	{
		cur->precision--;
		if (++len > 0)
			ft_putchar(*txt++);
		else
			ft_putchar('0');
	}
	while (cur->precision--)
		ft_putchar('0');
}

static int	sasha3(t_printf *cur, int len, int tmp, char *index)
{
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (cur->zero == ' ' && cur->sign)
		ft_putchar(cur->sign);
	put_float(cur, index, len);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	return (tmp);
}

int			to_float(t_printf *cur)
{
	int		len;
	int		tmp;
	char	*txt;
	char	*index;

	if (!(txt = get_number(cur, (char*)cur->content, &tmp, &len)))
		return (-1);
	if (tmp >= 0)
		index = ft_printf_multiply(txt + tmp, &len, tmp);
	else
		index = ft_printf_divide(txt, &len, tmp, cur->precision);
	tmp = cur->precision + (cur->sign > 0) + (cur->precision || cur->sharp);
	if (len > 0)
		tmp += len;
	else
		tmp += 1;
	if (cur->zero == '0' && cur->sign)
		ft_putchar(cur->sign);
	tmp = sasha3(cur, len, tmp, index);
	free(cur->content);
	free(txt);
	return (tmp - 1);
}
