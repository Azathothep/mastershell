/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:43:44 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/05/17 16:49:49 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static int	str_size_until_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '\"' || s[i] == '\'')
			i += matching_quote(&s[i], s[i]);
		i++;
	}
	return (i);
}

static char	*alloc_new_env_word(char *s)
{
	char	*token;
	int		len;

	len = str_size_until_space(s);
	token = malloc(sizeof(char) * (len + 3));
	if (!token)
	{
		errno = 1;
		return (NULL);
	}
	token[0] = '"';
	ft_strlcpy(&token[1], s, len + 1);
	token[len + 1] = '"';
	token[len + 2] = '\0';
	return (token);
}

static t_list	*new_env_word_list(char *s)
{
	char	*word;
	t_list	*lst;

	word = alloc_new_env_word(s);
	lst = ft_lstnew(word);
	if (!word || !lst)
	{
		errno = 1;
		ft_free(word);
		ft_lstdelone(lst, &lst_del);
		return (NULL);
	}
	return (lst);
}

static t_list	*cut_env(char *s)
{
	t_list	*begin_lst;
	t_list	*lst;
	int		i;

	i = 0;
	begin_lst = NULL;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			lst = new_env_word_list(&s[i]);
			if (!lst)
				return (0);
			ft_lstadd_back(&begin_lst, lst);
			i += str_size_until_space(&s[i]);
		}
		else
			i++;
	}
	return (begin_lst);
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

int	replace_all_env(t_list **begin_lexicon, t_mini *mini)
{
	char	*new_token;
	t_list	*prev;
	t_list	*lst;
	t_list	*to_insert;
	t_list	*next;

	lst = *begin_lexicon;
	prev = NULL;
	while (lst)
	{
		next = lst->next;
		new_token = translate(get_token(lst), &chunk_wquotes,
				&tl_only_env, mini);
		if (!new_token)
			return (0);
		to_insert = cut_env(new_token);
		free (new_token);
		if (!to_insert)
			return (0);
		prev = replace_lst_chain(begin_lexicon, to_insert, prev);
		lst = next;
	}
	return (1);
}
