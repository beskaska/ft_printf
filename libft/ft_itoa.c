/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:35:13 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/09 13:59:47 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long n)
{
	int			len;
	long long	nb;
	char		*res;

	len = 1;
	nb = n / 10;
	while (nb)
	{
		len++;
		nb /= 10;
	}
	if (n < 0)
		++len;
	res = (char*)malloc(len + 1);
	res[len] = 0;
	if (!res)
		return (NULL);
	res[0] = '-';
	while (len-- > 0)
	{
		res[len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (res);
}
