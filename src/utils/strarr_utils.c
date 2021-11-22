/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:48:03 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:48:08 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

char	**strarr_add(char **arr, char *new)
{
	char	**arr_new;
	int		size;
	int		i;

	size = 0;
	while (arr[size] != NULL)
		size++;
	arr_new = malloc(sizeof(char *) * (size + 2));
	if (arr_new == NULL)
		perror("error: strarr_add: malloc");
	else
	{
		i = 0;
		while (i < size)
		{
			arr_new[i] = arr[i];
			i++;
		}
		arr_new[i++] = new;
		arr_new[i] = NULL;
	}
	free(arr);
	return (arr_new);
}

/*
**
*/

void	strarr_del_at(char **arr, size_t i)
{
	free(arr[i]);
	while (1)
	{
		arr[i] = arr[i + 1];
		if (arr[i++] == NULL)
			break ;
	}
}

/*
**
*/

void	strarr_free(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] != NULL)
			free(arr[i++]);
		free(arr);
	}
}
