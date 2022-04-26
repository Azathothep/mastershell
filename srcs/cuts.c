/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:25 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/04/25 15:00:09 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/parsing.h"

static t_list	*empty_string( void )
{
	char	*token;
	t_list	*lst;

	token = malloc(sizeof(char));
	if (!token)
	{
		errno = 3;
		return (NULL);
	}
	token[0] = '\0';
	lst = ft_lstnew(token);
	if (!lst)
	{
		free(token);
		return (NULL);
	}
	return (lst);
}

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

static t_list	*freeall(t_list *begin_lst, t_list *lst, char *token)
{
	errno = 1;
	ft_free(token);
	ft_lstdelone(lst, &lst_del);
	ft_lstclear(&begin_lst, &lst_del);
	return (NULL);
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
			return (freeall(begin_lst, lst, token));
		ft_lstadd_back(&begin_lst, lst);
		i += (f)(s + i);
	}
	if (s[0] == '\0')
		begin_lst = empty_string();
	return (begin_lst);
}
