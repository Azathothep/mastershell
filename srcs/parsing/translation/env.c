/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:51:50 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/13 13:49:53 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/lib.h"

char	*pull_quotes(char *s)
{
	int		len;

	len = ft_strlen(s);
	ft_memmove(s, s + 1, len);
	if (len > 1)
		s[len - 2] = '\0';
	return (s);
}

static char	*ft_getenv(char const *s, t_list *env)
{
	char	*line;
	int		len;

	len = ft_strlen(s);
	while (env)
	{
		line = get_token(env);
		if (ft_strncmp(s, line, len) == 0)
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

char	*replace_env(char const *s, t_mini *mini)
{
	char	*env;

	if (s[1] == '?')
		env = ft_itoa(g_exitstatus);
	else
	{
		env = ft_getenv(&s[1], mini->envpl);
		if (!env)
			env = ft_strdup("");
		else
		{
			env = ft_strdup(env);
		}
	}
	if (!env)
	{
		errno = 1;
		return (NULL);
	}
	return (env);
}

char	*replace_env_in_word(char *word, t_mini *mini)
{
	char	*token;
	char	*translation;
	t_list	*lst;
	t_list	*begin_cutlst;

	begin_cutlst = cut_list(word, &chunk_nquotes);
	if (!begin_cutlst)
		return (NULL);
	lst = begin_cutlst;
	while (lst)
	{
		token = get_token(lst);
		if (token[0] == '$' && isenv(token[1]))
			token = replace_env(token, mini);
		replace_content(lst, token);
		lst = lst->next;
	}
	translation = lst_joinstr(&begin_cutlst);
	ft_lstclear(&begin_cutlst, &lst_del);
	if (!translation)
	{
		errno = 1;
		return (NULL);
	}
	return (translation);
}

t_list	*process_env(t_list *lst, t_mini *mini)
{
	int		len;
	char	*token;
	t_list	*cut_lst;

	token = get_token(lst);
	len = ft_strlen(token);
	if (isenv(token[1]))
	{
		token = replace_env(token, mini);
		cut_lst = cut_by_spaces(token);
		ft_free(token);
		return (cut_lst);
	}
	else if (token[1])
	{
		ft_memmove(token, &token[1], len);
		token[len - 2] = '\0';
	}
	return (lst);
}
