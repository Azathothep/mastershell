/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:16:37 by marvin            #+#    #+#             */
/*   Updated: 2022/03/21 15:16:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static char	*get_heredoc(t_list *lst)
{
	char	*token;
	char	*del;

	token = get_token(lst);
	del = get_token(lst->next);
	if (del && del[0] == '\"' && del[ft_strlen(del) - 1] == '\"')
	{
		del = pull_quotes(del);
		token = add_input(del, "quoted");
	}
	else if (!del || !ft_isalpha(del[0]))
	{
		if (!del || del[0] == '\0')
			del = "\\n";
		printf("mastershell: parse error near '%s'\n", del);
		return (NULL);
	}
	else
		token = add_input(del, "n_quoted");
	return (token);
}

static void	add_chevron(char const *sign, char *file, t_mini *mini)
{
	sign += 0;
	file += 0;
	mini += 0;
	return ;
}

void	process_chevrons(t_list **begin_lexicon, t_list *lst,
						t_list *prev_lst, t_mini *mini)
{
	char	*token;
	t_list	*lst_new;

	if (!ft_strncmp(get_token(lst), "<<", 2))
	{
		token = get_heredoc(lst);
		lst_new = ft_lstnew(token);
		if (!token || !lst_new)
		{
			ft_lstdelone(lst_new, &lst_del);
			ft_lstclear(begin_lexicon, &lst_del);
			return ;
		}
		insert_lst(begin_lexicon, lst_new, prev_lst);
		prev_lst = lst_new;
	}
	else
	{
		add_chevron(get_token(lst), get_token(lst->next), mini);
	}
	remove_lst(begin_lexicon, lst->next, lst);
	remove_lst(begin_lexicon, lst, prev_lst);
}
