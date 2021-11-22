/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:37:47 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/21 11:54:36 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	if (dst_size && dst_size > i + 1)
		ft_strlcpy(dst + i, src, dst_size - i);
	j = i + ft_strlen(src);
	return (j - ((i - dst_size) * (i > dst_size)));
}
