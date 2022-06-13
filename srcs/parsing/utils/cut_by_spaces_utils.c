/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_by_spaces_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:41:30 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/13 11:41:37 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/lib.h"

int	join_by_spaces(t_list **begin_lst)
{
	t_list	*lst;
	t_list	*next;
	char	*word;

	lst = *begin_lst;
	while (lst && lst->next)
	{
		next = lst->next;
		if (get_token(next))
		{
			word = ft_strjoin(get_token(lst), get_token(next));
			if (!word)
				return (set_errno_int(1));
			replace_content(lst, word);
			lst->next = next->next;
		}
		else
		{
			lst->next = next->next;
			lst = lst->next;
		}
		ft_lstdelone(next, &lst_del);
		next = NULL;
	}
	return (1);
}

int	set_errno_int(int n)
{
	errno = n;
	return (0);
}
