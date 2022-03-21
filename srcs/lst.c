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

void	insert_lst(t_list *lst, t_list *lst_new)
{
	t_list	*next_lst;

	next_lst = lst->next;
	lst->next = lst_new;
	lst_new->next = next_lst;
}
