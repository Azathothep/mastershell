/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:43:11 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/21 16:24:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../incs/parsing.h"
#include "../incs/lib.h"

static void	replace_content(t_list *lst, char *token)
{
	free(lst->content);
	lst->content = token;
}

char	*tl_only_env(char *s, int exit_status)
{
	if (s[0] == '$' && s[1])
		return (replace_env(s, exit_status));
	else
		return (s);
}

char	*translate(char const *token, char *(*f)(char *, int), int exit_status)
{
	t_list	*begin_cutlst;
	t_list	*lst;
	char	*translation;
	char	*word;

	begin_cutlst = cut_list(token, &chunk_wquotes);
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

static char	*tl_all(char *token, int exit_status)
{
	int	len;

	len = ft_strlen(token);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (pull_quotes(token));
	else if (token[0] == '\"' && token[len - 1] == '\"')
		return (translate(pull_quotes(token), &tl_only_env, exit_status));
	else if (token[0] == '$' && isenv(token[1]))
		return (replace_env(token, exit_status));
	return (token);
}

void	interpreter(t_list **begin_lst, int exit_status)
{
	t_list	*lst;
	char	*token;

	lst = *begin_lst;
	while (lst)
	{
		token = get_token(lst);
		if (!ft_strncmp(token, "<<", 2))
			lst = lst->next;
		else
		{
			token = translate(token, &tl_all, exit_status);
			if (!token)
			{
				ft_lstclear(begin_lst, &lst_del);
				return ;
			}
			if (token != lst->content)
				replace_content(lst, token);
		}
		if (lst)
			lst = lst->next;
	}
}
