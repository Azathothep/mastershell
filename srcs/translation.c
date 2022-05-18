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

static char *ft_getenv(char const *s, t_list *env)
{
	char	*line;
	int		len;

	len = ft_strlen(s);
	while (env)
	{
		line = get_token(env);
		if (strncmp(s, line, len) == 0)
		{
			if (line[len] == '=')
				return (&line[len + 1]);
			else if (!line[len])
				return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

static char	*replace_env(char const *s, t_mini *mini)
{
	char	*env;

	if (s[1] == '?')
		env = ft_itoa(mini->exit_status);
	else
	{
		env = ft_getenv(&s[1], mini->envpl);
		if (!env)
			env = translate(env, &chunk_nquotes, &tl_only_env,
				mini);
		else
			env = ft_strdup(env);
	}
	if (!env)
	{
		errno = 1;
		return (NULL);
	}
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

char	*tl_only_env(char *s, t_mini *mini)
{
	if (!s)
		return (NULL);
	if (s[0] == '$' && s[1])
		return (replace_env(s, mini));
	else
		return (s);
}

char	*tl_all(char *token, t_mini *mini)
{
	int	len;

	if (!token)
		return (NULL);
	len = ft_strlen(token);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (pull_quotes(token));
	else if (token[0] == '\"' && token[len - 1] == '\"')
		return (translate(pull_quotes(token), &chunk_nquotes,
				&tl_only_env, mini));
	else if (token[0] == '$' && isenv(token[1]))
		return (replace_env(token, mini));
	return (token);
}

char	*translate(char const *token, int (*chunk)(char const *),
					char *(*f)(char *, t_mini *), t_mini *mini)
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
		word = (f)(get_token(lst), mini);
		if (!word)
		{
			ft_lstclear(&begin_cutlst, &lst_del);
			return (NULL);
		}
		if (word != get_token(lst))
			ft_free(lst->content);
		lst->content = (void *)word;
		lst = lst->next;
	}
	translation = lst_joinstr(&begin_cutlst);
	ft_lstclear(&begin_cutlst, &lst_del);
	return (translation);
}
