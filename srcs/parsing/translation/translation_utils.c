/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:57:47 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/13 13:36:24 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/lib.h"

t_list	*replace_lst_chain(t_list **dest, t_list *src, t_list *prev_lst)
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

void	pop_null_lst(t_list **lexer_tab)
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
			if (token == NULL)
				remove_lst(&lexer_tab[i], lst);
			lst = lst->next;
		}
	}
}
