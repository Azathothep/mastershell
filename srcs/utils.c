/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:15 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/15 13:49:36 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdlib.h>
#include <stdio.h>

char	**ft_free_split(char **tab)
{
	int	index;

	index = -1;
	while (tab[++index])
		free(tab[index]);
	free(tab);
	return (NULL);
}

int	tabsize(char **tab)
{
	int	size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}
#include <stdio.h>
char	*append(char *str, char *add)
{
	char	*to_free;

	if (!add)
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	to_free = str;
	str = ft_strjoin(str, add);
	free (to_free);
	free (add);
	if (!str)
		return (NULL);
	return (str);
}
