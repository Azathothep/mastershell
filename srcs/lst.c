/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:21:28 by marvin            #+#    #+#             */
/*   Updated: 2022/03/21 15:21:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"
#include "../incs/parsing.h"

void	lst_del(void *content)
{
	ft_free((char *)content);
}

void	pop_pile(t_list **begin_lst)
{
	t_list	*next;

	if (!(*begin_lst))
		return ;
	next = (*begin_lst)->next;
	ft_lstdelone(*begin_lst, &lst_del);
	*begin_lst = next;
}

void	remove_lst(t_list **begin_lst, t_list *to_del)
{
	t_list	*prev_lst;
	t_list	*lst;

	prev_lst = NULL;
	lst = *begin_lst;
	if (!to_del)
		return ;
	while (lst != to_del)
	{
		prev_lst = lst;
		lst = lst->next;
	}
	if (prev_lst)
		prev_lst->next = lst->next;
	else
		*begin_lst = lst->next;
	ft_lstdelone(to_del, &lst_del);
	to_del = NULL;
}

void	insert_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst)
{
	if (!lst)
		return ;
	if (prev_lst)
	{
		lst->next = prev_lst->next;
		prev_lst->next = lst;
	}
	else
	{
		lst->next = (*begin_lst)->next;
		*begin_lst = lst;
	}
}

void	replace_content(t_list *lst, char *token)
{
	ft_free(lst->content);
	lst->content = token;
}
