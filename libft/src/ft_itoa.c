/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:00:46 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/19 11:32:28 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_len(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		len++;
	while (1)
	{
		n /= 10;
		if (n == 0)
			break ;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*a;
	int		len;

	len = itoa_len(n);
	a = malloc((len + 1) * sizeof(char));
	if (!a)
		return (NULL);
	a[0] = '-';
	a[len] = '\0';
	while (len--)
	{
		a[len] = n % 10;
		if (n < 0)
			a[len] = -a[len];
		a[len] += '0';
		n /= 10;
		if (n == 0)
			break ;
	}
	return (a);
}
