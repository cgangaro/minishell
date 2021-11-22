/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:31:07 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/08 21:31:11 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	if (src == NULL)
		return (NULL);
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
	return (dst);
}
