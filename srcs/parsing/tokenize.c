/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:40:13 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/08 10:30:29 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../incs/parsing.h"

static t_list	*freeall(t_list *begin_lst, t_list *lst, char *token)
{
	errno = 1;
	ft_free(token);
	ft_lstdelone(lst, &lst_del);
	ft_lstclear(&begin_lst, &lst_del);
	return (NULL);
}

static int	size_str(char const *s)
{
	int	i;

	i = 0;
	if (s[0] == '|')
		return (1);
	if (!ft_strncmp(s, "2>", 2) || !ft_strncmp(s, "1>", 2))
	{
		if (s[2] == '>')
			return (3);
		return (2);
	}
	if (s[0] == '<' || s[0] == '>')
	{
		i++;
		if (s[0] == s[1])
			i++;
		return (i);
	}
	while (s[i] && !ft_inbase(s[i], " <>|"))
	{
		if (s[i] == '\"' || s[i] == '\'')
			i += matching_quote(&s[i], s[i]);
		i++;
	}
	return (i);
}

static char	*alloc_token(char const *s)
{
	int		i;
	int		len;
	char	*str;

	i = -1;
	len = size_str(s);
	str = malloc (sizeof (char) * (len + 1));
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

t_list	*tokenize(char const *s)
{
	char	*token;
	t_list	*begin_lst;
	t_list	*lst;
	int		i;

	i = 0;
	begin_lst = NULL;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i])
	{
		token = alloc_token(s + i);
		lst = ft_lstnew(token);
		if (!token || !lst)
			return (freeall(begin_lst, lst, token));
		ft_lstadd_back(&begin_lst, lst);
		i += size_str(s + i);
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (begin_lst);
}
