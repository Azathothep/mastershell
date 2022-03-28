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

static char	*replace_env(char const *s, int exit_status)
{
	char	*env;

	if (s[1] == '?')
		env = ft_itoa(exit_status);
	else
	{
		env = getenv(&s[1]);
		if (!env)
			env = ft_strdup("");
		else
			env = ft_strdup(env);
	}
	if (!env)
		return (NULL);
	return (env);
}

char	*pull_quotes(char *s)
{
	int		len;

	len = ft_strlen(s);
	ft_memmove(s, s + 1, len);
	if (len > 1)
		s[len - 2] = '\0';
	return (s);
}

char	*tl_only_env(char *s, int exit_status)
{
	if (s[0] == '$' && s[1])
		return (replace_env(s, exit_status));
	else
		return (s);
}

char	*tl_all(char *token, int exit_status)
{
	int	len;

	len = ft_strlen(token);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (pull_quotes(token));
	else if (token[0] == '\"' && token[len - 1] == '\"')
		return (translate(pull_quotes(token), &chunk_wquotes,
				&tl_only_env, exit_status));
	else if (token[0] == '$' && isenv(token[1]))
		return (replace_env(token, exit_status));
	return (token);
}

char	*translate(char const *token, int (*chunk)(char const *),
					char *(*f)(char *, int), int exit_status)
{
	t_list	*begin_cutlst;
	t_list	*lst;
	char	*translation;
	char	*word;

	begin_cutlst = cut_list(token, chunk);
	if (!begin_cutlst)
		return (NULL);
	lst = begin_cutlst;
	while (lst)
	{
		word = (f)(get_token(lst), exit_status);
		if (!word)
		{
			ft_lstclear(&begin_cutlst, &lst_del);
			return (NULL);
		}
		if (word != get_token(lst))
			free(lst->content);
		lst->content = (void *)word;
		lst = lst->next;
	}
	translation = lst_joinstr(&begin_cutlst);
	ft_lstclear(&begin_cutlst, &lst_del);
	return (translation);
}
