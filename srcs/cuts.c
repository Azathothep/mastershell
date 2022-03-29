/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:25 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/29 14:08:35 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/parsing.h"

static char	*allocstr(char const *s, int len)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc (sizeof (*str) * (len + 1));
	if (!str)
	{
		errno = 1;
		return (NULL);
	}
	while (++i < len)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

t_list	*cut_list(char const *s, int (*f)(char const *))
{
	t_list	*begin_lst;
	t_list	*lst;
	char	*token;
	int		i;

	i = 0;
	lst = NULL;
	begin_lst = NULL;
	while (s[i])
	{
		token = allocstr(s + i, (f)(s + i));
		lst = ft_lstnew((void *)token);
		if (!token || !lst)
		{
			errno = 1;
			free(token);
			ft_lstdelone(lst, &lst_del);
			ft_lstclear(&begin_lst, &lst_del);
			return (NULL);
		}
		ft_lstadd_back(&begin_lst, lst);
		i += (f)(s + i);
	}
	return (begin_lst);
}
