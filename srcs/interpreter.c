/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:43:11 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/21 12:01:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../incs/parsing.h"
#include "../incs/lib.h"

int	isenv(char c)
{
	if (ft_isalnum(c) || c == '?')
		return (1);
	return (0);
}

static char	*add_translate(char *translation, char *cut_str, int exit_status)
{
	int	len;

	len = ft_strlen(cut_str);
	if (cut_str[0] == '\'' && cut_str[len - 1] == '\'')
		translation = append(translation, pull_quotes(cut_str));
	else if (cut_str[0] == '\"' && cut_str[len - 1] == '\"')
		translation = append(translation, double_quotes(pull_quotes(cut_str), exit_status));
	else if (cut_str[0] == '$' && isenv(cut_str[1]))
		translation = append(translation, replace_env(cut_str, exit_status));
	else
		translation = append(translation, ft_strdup(cut_str));
	if (!translation)
		return (NULL);
	return (translation);
}

static char	*interpret_token(char const *token, int exit_status)
{
	int		i;
	char	**cut_tab;
	char	*translation;

	i = -1;
	cut_tab = cut(token, "w_quotes");
	translation = NULL;
	if (!cut_tab)
		return (NULL);
	while (cut_tab[++i])
		translation = add_translate(translation, cut_tab[i], exit_status);
	free_tabtwo(cut_tab);
	return (translation);
}

void	interpreter(t_list **begin_lst, int exit_status)
{
	t_list	*lst;
	char	*token;

	lst = *begin_lst;
	while (lst)
	{
		token = interpret_token(get_token(lst), exit_status);
		if (!token)
		{
			ft_lstclear(begin_lst, &lst_del);
			return ;
		}
		free(lst->content);
		lst->content = (void *)token;
		lst = lst->next;
	}
}
