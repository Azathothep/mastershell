/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:31:39 by marvin            #+#    #+#             */
/*   Updated: 2022/03/16 11:31:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/lib.h"

char	*replace_env(char const *s, int exit_status)
{
	char	*env;

	if (s[1] == '?')
		env = ft_itoa(exit_status);
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

char	*pull_quotes(char const *s)
{
	int		len;
	char	*ret;

	len = ft_strlen(s);
	ret = malloc (sizeof(char) * (len - 1));
	if (ret)
		ft_strlcpy(ret, s + 1, len - 1);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*double_quotes(char const *s, int exit_status)
{
	int		i;
	char	*no_quotes;
	char	*ret;
	char	**cut_tab;

	i = -1;
	no_quotes = pull_quotes(s);
	if (!no_quotes)
		return (NULL);
	cut_tab = cut(no_quotes, "n_quotes");
	free (no_quotes);
	ret = NULL;
	if (!cut_tab)
		return (NULL);
	while (cut_tab[++i])
	{
		if (cut_tab[i][0] == '$' && cut_tab[i][1])
			ret = append(ret, replace_env(cut_tab[i], exit_status));
		else
			ret = append(ret, ft_strdup(cut_tab[i]));
		if (!ret)
			return (NULL);
	}
	free_tabtwo(cut_tab);
	return (ret);
}
