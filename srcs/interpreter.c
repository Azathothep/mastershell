/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:43:11 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/15 11:27:27 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../incs/parsing.h"

static char	*replace_env(char const *s)
{
	char	*env;

	if (s[1] == '$')
		env = ft_itoa(getpid());
	else
	{
		env = ft_strdup(getenv(&s[1]));
		if (!env)
			env = ft_strdup("");
	}
	if (!env)
		return (NULL);
	return (env);
}

static char	*pull_quotes(char const *s)
{
	int		len;
	char	*ret;

	len = ft_strlen(s);
	ret = malloc (sizeof(char) * (len - 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + 1, len - 1);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*single_quotes(char const *s)
{
	int		i;
	char	*ret;
	char	**cut_tab;

	i = -1;
	cut_tab = cut(pull_quotes(s), "n_quotes");
	if (!cut_tab)
		return (NULL);
	while (cut_tab[++i])
	{
		if (cut_tab[i][0] == '$' && cut_tab[i][1])
			ret = append(ret, replace_env(cut_tab[i]));
		else
			ret = append(ret, cut_tab[i]);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

static char	*interpret_token(char const *token)
{
	int		i;
	int		len;
	char	**cut_tab;
	char	*translation;

	i = -1;
	cut_tab = cut(token, "w_quotes");
	translation = NULL;
	if (!cut_tab)
		return (NULL);
	while (cut_tab[++i])
	{
		len = ft_strlen(cut_tab[i]);
		if (cut_tab[i][0] == '\"' && cut_tab[i][len - 1] == '\"')
			translation = append(translation, pull_quotes(cut_tab[i]));
		else if (cut_tab[i][0] == '\'' && cut_tab[i][len - 1] == '\'')
			translation = append(translation, single_quotes(cut_tab[i]));
		else if (cut_tab[i][0] == '$' && cut_tab[i][1])
			translation = append(translation, replace_env(cut_tab[i]));
		else
			translation = append(translation, cut_tab[i]);
		if (!translation)
			return (NULL);
	}
	return (translation);
}

char	**interpreter(char **lexicon)
{
	int		i;
	int		w_i;
	int		size;
	char	**translate;

	i = -1;
	w_i = 0;
	size = tabsize(lexicon);
	translate = malloc(sizeof (char *) * (size + 1));
	if (!translate)
		return (NULL);
	while (++i < size)
	{
		translate[w_i] = interpret_token(lexicon[i]);
		if (!translate[w_i])
			return (ft_free_split(translate));
		if (translate[w_i][0] == '\0')
		{
			free (translate[w_i]);
			w_i--;
		}
		++w_i;
	}
	translate[w_i] = NULL;
	return (translate);
}
