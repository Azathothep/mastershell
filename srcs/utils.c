/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:15 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/22 10:56:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdlib.h>
#include <stdio.h>

int	isenv(char c)
{
	if (ft_isalnum(c) || c == '?')
		return (1);
	return (0);
}

char	*get_token(t_list *lst)
{
	if (!lst)
		return (NULL);
	return ((char *)lst->content);
}

char	*lst_joinstr(t_list **begin_lst)
{
	t_list	*lst;
	int		size;
	char	*str;

	size = 0;
	lst = *begin_lst;
	while (lst)
	{
		size += ft_strlen(get_token(lst));
		lst = lst->next;
	}
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	lst = *begin_lst;
	size = 0;
	while (lst)
	{
		ft_strlcpy(str + size, get_token(lst), ft_strlen(get_token(lst)) + 1);
		size += ft_strlen(get_token(lst));
		lst = lst->next;
	}
	return (str);
}
