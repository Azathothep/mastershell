/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_by_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:17 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/08 10:56:08 by fbelthoi         ###   ########.fr       */
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
				return (0);
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

t_list	*cut_by_spaces(char *s)
{
	t_list	*begin_lst;
	t_list	*lst;
	int		i;

	i = 0;
	begin_lst = NULL;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != ' ')
		{
			lst = new_env_word_list(&s[i]);
			i += str_size_until_space(&s[i]);
		}
		else
		{
			lst = ft_lstnew(NULL);
			while (s[i] == ' ')
				i++;
		}
		if (!lst)
		{
			ft_lstclear(&begin_lst, &lst_del);
			return (0);
		}
		ft_lstadd_back(&begin_lst, lst);
	}
	if (i == 0)
		return (ft_lstnew(NULL));
	return (begin_lst);
}
