/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:19:36 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/19 12:05:53 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*r;
	int		len;

	len = ft_strlen(src);
	r = malloc((len + 1) * sizeof(char));
	if (!r)
		return (NULL);
	ft_strlcpy(r, src, len + 1);
	return (r);
}
