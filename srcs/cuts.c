/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:25 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/15 11:27:19 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/parsing.h"

static char	*allocstr(char const *s, int len)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc (sizeof (*str) * (len + 1));
	if (!str)
		return (NULL);
	while (++i < len)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

static int	get_chunk(char const *s, char const *mode)
{
	if (!ft_strncmp(mode, "w_quotes", 8))
		return (chunk_wquotes(s));
	else if (!ft_strncmp(mode, "n_quotes", 8))
		return (chunk_nquotes(s));
	return (-1);
}

static int	cutsize(char const *s, char const *mode)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		size++;
		i += get_chunk(&s[i], mode);
	}
	return (size);
}

char	**cut(char const *s, char const *mode)
{
	char	**tab;
	int		i;
	int		len;
	int		size;
	int		tab_index;

	if (!s)
		return (NULL);
	size = cutsize(s, mode);
	tab = malloc (sizeof (*tab) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tab_index = -1;
	while (++tab_index < size)
	{
		len = get_chunk(s + i, mode);
		tab[tab_index] = allocstr(s + i, len);
		if (!tab[tab_index])
			return (ft_free_split(tab));
		i += len;
	}
	tab[tab_index] = NULL;
	return (tab);
}
