/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 00:35:42 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/23 20:59:00 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_abs(long long n)
{
	long long	mask;

	mask = n >> (sizeof(long long) * 8 - 1);
	return (n + mask ^ mask);
}
