/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:15 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/08 10:30:10 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/lib.h"

int	parse_error(const char *s)
{
	errno = 100;
	printf("mastershell: syntax error near `%s'\n", s);
	g_exitstatus = 258;
	return (0);
}

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

static int	joinlst_size(t_list **begin_lst)
{
	t_list	*lst;
	int		size;

	size = 0;
	lst = *begin_lst;
	while (lst)
	{
		size += ft_strlen(get_token(lst));
		lst = lst->next;
	}
	return (size);
}

char	*lst_joinstr(t_list **begin_lst)
{
	t_list	*lst;
	int		size;
	char	*str;

	if (!begin_lst)
		return (NULL);
	lst = *begin_lst;
	size = joinlst_size(begin_lst);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
	{
		errno = 1;
		return (NULL);
	}
	size = 0;
	while (lst)
	{
		ft_strlcpy(str + size, get_token(lst), ft_strlen(get_token(lst)) + 1);
		size += ft_strlen(get_token(lst));
		lst = lst->next;
	}
	return (str);
}
