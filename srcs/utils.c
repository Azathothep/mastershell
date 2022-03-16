/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:15 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/16 11:33:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdlib.h>
#include <stdio.h>

char	**free_tabtwo(char **tab)
{
	int	index;

	index = -1;
	if (!tab)
		return (NULL);
	while (tab[++index])
		free(tab[index]);
	free(tab);
	tab = NULL;
	return (NULL);
}

char	***free_cmd(char ***commands)
{
	int	i;
	int	j;

	i = -1;
	if (commands)
	{
		while (commands[++i])
		{
			j = -1;
			while (commands[i][++j])
				free(commands[i][j]);
			free(commands[i]);
		}
		free(commands);
		commands = NULL;
	}
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

void	lst_del(void *content)
{
	free((char *)content);
}
