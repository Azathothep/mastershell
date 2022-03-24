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

void	pop_lst(t_list **begin_lst)
{
	t_list	*next;

	if (!(*begin_lst))
		return ;
	next = (*begin_lst)->next;
	ft_lstdelone(*begin_lst, &lst_del);
	*begin_lst = next;
}

t_list	*remove_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	if (prev_lst)
	{
		prev_lst->next = lst->next;
		temp = prev_lst;
	}
	else
	{
		*begin_lst = lst->next;
		temp = *begin_lst;
	}
	ft_lstdelone(lst, &lst_del);
	return (temp);
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
	free(lst->content);
	lst->content = token;
}
