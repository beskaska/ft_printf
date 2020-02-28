/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:34:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/28 22:14:46 by aimelda          ###   ########.fr       */
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
	txt = ft_strnew(*len + ft_abs(exp));//just malloc?
	nb = *len - 1;
	while (n)
	{
		txt[nb--] = n % 10 + '0';
		n = n / 10;
	}
	return (txt);
}

static char	*multiply(char *num, int *len, int exp)
{
	int		i;
	int 	offset;
	char	oida;
	char	tmp;

	offset = *len;
	if (exp < 0)
		while (exp++)//optimize by comparing the precision and len
		{
			i = offset - *len;
			oida = 0;
			while (num[i])
			{
				tmp = num[i];
				num[i] = (num[i] - '0') / 2 + oida + '0';
				if (tmp % 2)
					oida = 5;
				else
					oida = 0;
				i++;
			}
			if (num[offset - *len] == '0')
				--(*len);
			if (oida)
				num[i] = '5';
		}
	return (num + offset - *len);
}

static char	*get_number(char *txt, int *tmp, int *len)//*cur not used
{
	short	exp;

	//if special values: +0; -0; NaN; +infinity; -infinity
	if ((exp = *(short*)(txt + 8)) < 0)
		exp = exp ^ (short)-32768;
	*tmp = exp - EXPONENT_BIAS - (sizeof(long long) * 8 - 1);
	return (num_to_txt(*(unsigned long long*)(txt), *tmp, len));
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
	while(cur->precision && *txt)
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

int			to_float(t_printf *cur, long double n)
{
	int		len;
	int		tmp;
	char	*txt;
	char	*index;

	if (((char*)cur->content)[9] < 0)
		cur->sign = '-';
	txt = get_number((char*)cur->content, &tmp, &len);
	index = multiply(txt, &len, tmp);
	tmp = cur->precision + (cur->sign > 0) + (cur->precision || cur->sharp);
	if (len > 0)
		tmp += len;
	else
		tmp += 1;
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	ft_putchar(cur->sign);
	put_float(cur, index, len);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	free(txt);
	return (tmp - 1);
}
