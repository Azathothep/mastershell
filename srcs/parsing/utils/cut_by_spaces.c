/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_by_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:17 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/13 11:41:18 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/mini.h"
#include "../../../incs/lib.h"

static int	str_size_until_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

static char	*alloc_new_env_word(char *s)
{
	char	*token;
	int		len;

	len = str_size_until_space(s);
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
	{
		errno = 1;
		return (NULL);
	}
	ft_strlcpy(token, s, len + 1);
	token[len] = '\0';
	return (token);
}

static t_list	*new_env_word_list(char *s)
{
	char	*word;
	t_list	*lst;

	word = alloc_new_env_word(s);
	lst = ft_lstnew(word);
	if (!word || !lst)
	{
		errno = 1;
		ft_free(word);
		ft_lstdelone(lst, &lst_del);
		return (NULL);
	}
	return (lst);
}

static int	cut_loop(t_list **begin_lst, char *s)
{
	t_list	*lst;
	int		i;

	i = 0;
	if (*s != ' ')
	{
		lst = new_env_word_list(s);
		i = str_size_until_space(s);
	}
	else
	{
		lst = ft_lstnew(NULL);
		while (s[i] == ' ')
			i++;
	}
	if (!lst)
	{
		ft_lstclear(begin_lst, &lst_del);
		return (-1);
	}
	ft_lstadd_back(begin_lst, lst);
	return (i);
}

t_list	*cut_by_spaces(char *s)
{
	t_list	*begin_lst;
	int		i;
	int		ret;

	i = 0;
	begin_lst = NULL;
	if (!s)
		return (NULL);
	while (s[i])
	{
		ret = cut_loop(&begin_lst, &s[i]);
		if (ret < 0)
			return (0);
		i += ret;
	}
	if (i == 0)
		return (ft_lstnew(NULL));
	return (begin_lst);
}
