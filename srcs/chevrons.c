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
	if (!ft_isalpha(filename[0]) && filename[0] != '$')
		return (0);
	return (1);
}

static char	*get_heredoc(t_list *lst)
{
	char	*token;
	char	*del;
	int		len;

	token = get_token(lst);
	del = get_token(lst->next);
	len = ft_strlen(del);
	if (del && del[0] == '\"' && del[len - 1] == '\"')
	{
		del = pull_quotes(del);
		token = add_input(del, "quoted");
	}
	else if (!del || !format_ok(del))
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

static int	add_chevron(char const *sign, char *token, t_mini *mini, int index)
{
	t_list	*lst_new;

	if (!format_ok(token))
	{
		printf("mastershell: parsing error near %s\n", sign);
		return (0);
	}
	if (!token)
		return (0);
	lst_new = ft_lstnew(ft_strdup(token));
	if (!lst_new || !(lst_new->content))
	{
		ft_lstdelone(lst_new, &lst_del);
		return (0);
	}
	if (sign[0] == '<')
		ft_lstadd_back(&(mini->infile[index].files), lst_new);
	else if (sign[0] == '>')
	{
		if (sign[1] == '>')
			mini->outfile[index].type = 0;
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
		token = get_heredoc(lst);
		if (!token)
			return (0);
		if (mini->heredocs[index]->content == NULL)
			mini->heredocs[index]->content = token;
		else
		{
			lst_new = ft_lstnew(token);
			if (!lst_new)
			{
				free (token);
				return (0);
			}
			ft_lstadd_back(&(mini->heredocs[index]), lst_new);
		}
	}
	else
		if (!add_chevron(get_token(lst), get_token(lst->next), mini, index))
			return (0);
	return (1);
}

void	process_chevrons(t_list **begin_lexicon, t_mini *mini)
{
	t_list	*lst;
	t_list	*prev_lst;
	int		index;

	index = 0;
	lst = *begin_lexicon;
	prev_lst = NULL;
	while (lst)
	{
		if (!ft_strncmp(get_token(lst), "|\0", 2))
			index++;
		else if (ft_inbase(get_token(lst)[0], "<>"))
		{
			if (!treat_chevron(lst, mini, index))
			{
				ft_lstclear(begin_lexicon, &lst_del);
				return ;
			}
			lst = remove_lst(begin_lexicon, lst->next, lst);
			lst = remove_lst(begin_lexicon, lst, prev_lst);
		}
		prev_lst = lst;
		lst = lst->next;
	}
}
