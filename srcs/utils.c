/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:15 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/21 11:34:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdlib.h>
#include <stdio.h>

int	tabsize(char **tab)
{
	int	size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

char	*append(char *str, char *add)
{
	char	*to_free;

	if (!add)
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	to_free = str;
	str = ft_strjoin(str, add);
	free (to_free);
	free (add);
	if (!str)
		return (NULL);
	return (str);
}

char	*get_token(t_list *lst)
{
	return ((char *)lst->content);
}

char	*lst_joinstr(t_list **begin_lst)
{
	t_list *lst;
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