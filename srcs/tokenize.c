/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:40:13 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/16 11:11:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/parsing.h"

static int	get_other(char const *s, char c)
{
	int	j;
	int	other;

	j = ft_strlen(s);
	other = 0;
	while (--j > 0)
		if (s[j] == c)
			other = j;
	return (other);
}

static int	alloc_token(char **str, char const *s)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (s[len] && s[len] != ' ')
	{
		if (s[len] == '\"' || s[len] == '\'')
			len += get_other(&s[len], s[len]);
		len++;
	}
	*str = malloc (sizeof (char) * (len + 1));
	if (!(*str))
		return (0);
	while (++i < len)
		(*str)[i] = s[i];
	(*str)[i] = '\0';
	return (len);
}

static int	get_size(char const *s)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i])
			size++;
		while (s[i] && s[i] != ' ')
		{
			if (s[i] == '\"' || s[i] == '\'')
				i += get_other(&s[i], s[i]);
			i++;
		}
	}
	return (size);
}

char	**tokenize(char const *s)
{
	char	**tab;
	int		i;
	int		size;
	int		tab_index;

	size = get_size(s);
	tab = malloc (sizeof (char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tab_index = -1;
	while (++tab_index < size)
	{
		while (s[i] && s[i] == ' ')
			i++;
		i += alloc_token(&tab[tab_index], s + i);
		if (!tab[tab_index])
			return (free_tabtwo(tab));
		i++;
	}
	tab[tab_index] = NULL;
	return (tab);
}
