/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:40:13 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/21 17:25:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/parsing.h"

static int	get_other(char const *s, char c)
{
	int	j;
	int	other;

	j = ft_strlen(s);
	other = 0;
	while (--j > 0)
		if (s[j] == c)
			other = j;
	return (other);
}

static int	size_str(char const *s)
{
	int	i;

	i = 0;
	if (s[0] == '<' || s[0] == '>')
	{
		i++;
		if (s[0] == s[1])
			i++;
		return (i);
	}
	while (s[i] && !ft_inbase(s[i], " <>"))
	{
		if (s[i] == '\"' || s[i] == '\'')
			i += get_other(&s[i], s[i]);
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
		return (NULL);
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
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		token = alloc_token(s + i);
		lst = ft_lstnew((void *)token);
		if (!token || !lst)
		{
			ft_lstclear(&begin_lst, &lst_del);
			return (NULL);
		}
		ft_lstadd_back(&begin_lst, lst);
		i += size_str(s + i);
	}
	return (begin_lst);
}
