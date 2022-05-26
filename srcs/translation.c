/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:59:32 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/05/26 11:29:34 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/lib.h"

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
		env = ft_itoa(exitstatus);
	else
	{
		env = ft_getenv(&s[1], mini->envpl);
		if (!env)
		{
			env = ft_strdup("");
		}
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

static char	*replace_env_in_word(char *word, t_mini *mini)
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

static t_list *process_env(t_list *lst, t_mini *mini)
{
	int		len;
	char	*token;
	
	token = get_token(lst);
	len = ft_strlen(token);
	if (isenv(token[1]))
		return (cut_by_spaces(replace_env(token, mini)));
	else if (token[1])
	{
		ft_memmove(token, &token[1], len);
		token[len - 2] = '\0';
	}
	return (lst);
}

static t_list	*translate_token(t_list *lst, t_mini *mini)
{
	int		len;
	char	*token;

	token = get_token(lst);
	if (!token)
		return (NULL);
	len = ft_strlen(token);
	if (token[0] == '\'' && token[len - 1] == '\'')
	{
		replace_content(lst, pull_quotes(token));
	}
	else if (token[0] == '\"' && token[len - 1] == '\"')
	{
		replace_content(lst, replace_env_in_word(pull_quotes(token), mini));
	}
	else if (token[0] == '$')
	{
		return (process_env(lst, mini));
	}
	return (lst);
}

static t_list	*replace_lst_chain(t_list **dest, t_list *src, t_list *prev_lst)
{
	t_list	*next;
	t_list	*last;
	t_list	*to_del;

	if (prev_lst)
	{
		to_del = prev_lst->next;
		next = to_del->next;
		prev_lst->next = src;
	}
	else
	{
		to_del = *dest;
		next = (*dest)->next;
		*dest = src;
	}
	last = ft_lstlast(src);
	last->next = next;
	ft_lstdelone(to_del, &lst_del);
	return (last);
}

char	*translate_heredoc(char *line, t_mini *mini)
{
	t_list	*lst;
	t_list	*begin_cutlst;
	char	*final_line;

	begin_cutlst = cut_list(line, &chunk_nquotes);
	if (!begin_cutlst)
		return (NULL);
	lst = begin_cutlst;
	while (lst)
	{
		replace_content(lst, replace_env_in_word(get_token(lst), mini));
		lst = lst->next;
	}
	if (join_by_spaces(&begin_cutlst) == 0)
	{
		errno = 1;
		return (NULL);
	}
	final_line = lst_joinstr(&begin_cutlst);
	ft_lstclear(&begin_cutlst, &lst_del);
	return (final_line);
}

void	replace_chain(t_list **lst, t_list *new_chain, t_list **prev_lst,
						t_list **begin_cutlst)
{
	if (*lst == new_chain)
	{
		*prev_lst = *lst;
		*lst = (*lst)->next;
	}
	else
	{
		*prev_lst = replace_lst_chain(begin_cutlst, new_chain, *prev_lst);
		*lst = (*prev_lst)->next;
	}
}

t_list	*translate_word(t_list *to_translate, t_mini *mini)
{
	t_list	*lst;
	t_list	*new_chain;
	t_list	*prev_lst;
	t_list	*begin_cutlst;

	begin_cutlst = cut_list(get_token(to_translate), &chunk_wquotes);
	if (!begin_cutlst)
		return (NULL);
	prev_lst = NULL;
	lst = begin_cutlst;
	while (lst)
	{
		new_chain = translate_token(lst, mini);
		if (!new_chain)
		{
			return (NULL); // free some stuff?
		}
		replace_chain(&lst, new_chain, &prev_lst, &begin_cutlst);
	}
	join_by_spaces(&begin_cutlst);
	return (begin_cutlst);
}

static void	pop_null_lst(t_list **lexer_tab)
{
	t_list	*lst;
	char	*token;
	int		i;

	i = -1;
	while (lexer_tab[++i])
	{
		lst = lexer_tab[i];
		while (lst)
		{
			token = get_token(lst);
			if (token == NULL || token[0] == '\0')
				remove_lst(&lexer_tab[i], lst);
			lst = lst->next;
		}
	}
}

int	translation_lexertab(t_list **lexer_tab, t_mini *mini)
{
	t_list	*lst;
	t_list	*prev_lst;
	t_list	*new_chain;
	int		i;

	i = -1;
	while (lexer_tab[++i])
	{
		prev_lst = NULL;
		lst = lexer_tab[i];
		while (lst)
		{
			new_chain = translate_word(lst, mini);
			if (!new_chain)
				return (0);
			prev_lst = replace_lst_chain(&lexer_tab[i], new_chain, prev_lst);
			lst = prev_lst->next;
		}
	}
	pop_null_lst(lexer_tab);
	return (1);
}
