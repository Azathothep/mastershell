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

#include "../../../incs/parsing.h"
#include "../../../incs/lib.h"

static t_list	*translate_token(t_list *lst, t_mini *mini)
{
	int		len;
	char	*token;
	char	*token_enved;

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
		token_enved = replace_env_in_word(pull_quotes(token), mini);
		if (errno == 1)
			return (NULL);
		replace_content(lst, token_enved);
	}
	else if (token[0] == '$')
		return (process_env(lst, mini));
	return (lst);
}

char	*translate_heredoc(char *line, t_mini *mini)
{
	t_list	*lst;
	t_list	*begin_cutlst;
	char	*final_line;
	char	*token_enved;

	begin_cutlst = cut_list(line, &chunk_nquotes);
	if (!begin_cutlst)
		return (NULL);
	lst = begin_cutlst;
	while (lst)
	{
		token_enved = replace_env_in_word(get_token(lst), mini);
		if (errno == 1)
		{
			ft_lstclear(&begin_cutlst, &lst_del);
			return (NULL);
		}
		replace_content(lst, replace_env_in_word(get_token(lst), mini));
		lst = lst->next;
	}
	if (join_by_spaces(&begin_cutlst) == 0)
		return (NULL);
	final_line = lst_joinstr(&begin_cutlst);
	ft_lstclear(&begin_cutlst, &lst_del);
	return (final_line);
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
			ft_lstclear(&begin_cutlst, &lst_del);
			return (NULL);
		}
		replace_chain(&lst, new_chain, &prev_lst, &begin_cutlst);
	}
	join_by_spaces(&begin_cutlst);
	return (begin_cutlst);
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
