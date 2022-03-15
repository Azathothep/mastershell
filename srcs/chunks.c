/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:42:28 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/15 11:27:11 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/parsing.h"

static int	matching_quote(char const *s, char c)
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

static int	get_endenv(char const *s)
{
	int	i;

	i = 1;
	if (s[1] == '$')
		return (2);
	else
		while (s[i] && !ft_inbase(s[i], "\"\'$"))
			i++;
	return (i);
}

int	chunk_nquotes(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$' && s[i + 1])
		{
			if (i == 0)
				return (get_endenv(&s[i]));
			else
				return (i);
		}
		i++;
	}
	return (i);
}

static int	quote_index(int i, int quote)
{
	if (i == 0)
		return (quote + 1);
	else
		return (i);
}

int	chunk_wquotes(char const *s)
{
	int	i;
	int	quote;

	i = 0;
	while (s[i])
	{
		while (s[i] && !ft_inbase(s[i], "\"\'$"))
			i++;
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = matching_quote(&s[i], s[i]);
			if (quote > 0)
				return (quote_index(i, quote));
		}
		else if (s[i] == '$' && s[i + 1])
		{
			if (i == 0)
				return (get_endenv(&s[i]));
			else
				return (i);
		}
		i++;
	}
	return (i);
}
