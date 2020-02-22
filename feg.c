/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:34:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/22 23:54:53 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*num_to_txt(unsigned long long n, int *len, int exp)
{
	int		nb;
	char	*txt;

	*len = 1;
	nb = n;
	while (nb /= 10)
		(*len)++;
	txt = ft_strnew(MAX_LLONG_DIGIT + 1);
	if (exp < 0)
		nb = *len + 1;
	else
		nb = MAX_LLONG_DIGIT + 1;
	while (n)
	{
		txt[nb--] = n % 10 + '0';
		n = n / 10;
	}
	txt[nb] = '1';
	return (txt);
}

static char	*multiply(char *num, int *len, int *len_frac, int exp)
{
	char	offset;
	char	i;
	char	oida;
	char	tmp;

	if (exp < 0)
	{
		exp *= -1;
		while (exp--)
		{
			if (num[0] == '1')
			{
				offset = 1;
				(*len_frac)++;
			}
			else
				offset = 0;
			i = 0;
			oida = 0;
			while (i <= MAX_LLONG_DIGIT + 1) //may optimize by non-checking 0 chars
			{
				if (!num[i])
				{
					if (oida)
					{
						num[i] = '0';
						(*len)++;
					}
					else
						break;
				}
				tmp = num[i];
				if (i >= offset)
					num[i] = (num[i] - '0') / 2 + oida + '0';
				if (tmp == 1)
					oida = 5;
				else
					oida = 0;
				i++;
			}

		}
	}
	return (num);
}

static char	*get_number(t_printf *cur, char *txt, int *len, int *len_frac)
{
	char	*num_txt;
	short	exp;

	if ((exp = (short)(txt + 8)) < 0)
		exp = exp ^ (short)-32768;
	exp -= 16383;
	printf("%hd\n", exp);
	num_txt = num_to_txt((unsigned long long)(txt), len_frac, exp);
	return (multiply(num_txt, len, len_frac, exp));
}

static void	put_float(t_printf *cur, char *txt, int len, int len_frac)
{
	while (len-- > len_frac)
		ft_putchar(*txt++);
	if (cur->sharp)
		ft_putchar('.');
	while(len_frac--)
		ft_putchar(*txt++);
}

int			to_float(t_printf *cur, long double n)
{
	int		len;
	int		len_frac;
	int		tmp;
	char	*txt;

	if (((char*)cur->content)[10] < 0)
		cur->sign = '-';
	txt = get_number(cur, (char*)cur->content, &len, &len_frac);
	tmp = ft_max(len - len_frac, 0) + cur->precision + cur->sign > 0; //ony char for dec point?
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	ft_putchar(cur->sign);
	put_float(cur, txt, len, len_frac);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	free(txt);
	return (tmp - 1);
}
