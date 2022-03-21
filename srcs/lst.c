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

void	remove_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst)
{
	if (!lst)
		return ;
	if (prev_lst)
		prev_lst->next = lst->next;
	else
		*begin_lst = lst->next;
	ft_lstdelone(lst, &lst_del);
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
