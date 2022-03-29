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

static int	format_ok(char const *filename)
{
	if (!filename || (!ft_isalpha(filename[0]) && filename[0] != '$'))
		return (0);
	return (1);
}

static char	*get_heredoc(t_list *lst, int exit_status)
{
	char	*token;
	char	*del;

	token = get_token(lst);
	del = get_token(lst->next);
	if (!del || !format_ok(del))
	{
		if (!del || del[0] == '\0')
			del = "\\n";
		errno = 100;
		printf("mastershell: syntax error near '%s'\n", del);
		return (NULL);
	}
	else
		token = add_input(del, exit_status);
	return (token);
}

static int	add_chevron(char const *sign, char *token, t_mini *mini, int index)
{
	t_list	*lst_new;
	char	*token_dup;

	lst_new = NULL;
	if (!format_ok(token))
		return (parse_error(sign));
	token_dup = ft_strdup(token);
	lst_new = ft_lstnew(token_dup);
	if (!token_dup || !lst_new)
	{
		errno = 1;
		free(token_dup);
		ft_lstdelone(lst_new, &lst_del);
		return (0);
	}
	if (sign[0] == '<')
		ft_lstadd_back(&(mini->infile[index].files), lst_new);
	else if (sign[0] == '>')
	{
		if (sign[1] == '>')
			mini->outfile[index].type = 1;
		ft_lstadd_back(&(mini->outfile[index].files), lst_new);
	}
	return (1);
}

static int	treat_chevron(t_list *lst, t_mini *mini, int index)
{
	char	*token;
	t_list	*lst_new;

	if (!ft_strncmp(get_token(lst), "<<", 2))
	{
		token = get_heredoc(lst, mini->exit_status);
		if (!token)
			return (0);
		if (mini->heredocs[index]->content == NULL)
			mini->heredocs[index]->content = token;
		else
		{
			lst_new = ft_lstnew(token);
			if (!lst_new)
			{
				errno = 1;
				return (ft_free(token));
			}
			ft_lstadd_back(&(mini->heredocs[index]), lst_new);
		}
	}
	else
		if (!add_chevron(get_token(lst), get_token(lst->next), mini, index))
			return (0);
	return (1);
}

int	process_chevrons(t_list **begin_lexicon, t_mini *mini)
{
	t_list	*lst;
	t_list	*temp;
	int		index;

	index = 0;
	lst = *begin_lexicon;
	while (lst)
	{
		if (!ft_strncmp(get_token(lst), "|\0", 2))
			index++;
		if (ft_inbase(get_token(lst)[0], "<>"))
		{
			if (!treat_chevron(lst, mini, index))
				return (0);
			temp = lst->next->next;
			remove_lst(begin_lexicon, lst->next);
			remove_lst(begin_lexicon, lst);
			lst = temp;
		}
		else
			lst = lst->next;
	}
	return (1);
}
