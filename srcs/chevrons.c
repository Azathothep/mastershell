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

t_list	**init_heredocs(int cmd_nb)
{
	int	i;
	t_list	**heredocs;

	i = -1;
	heredocs = malloc(sizeof(t_list *) * (cmd_nb + 1));
	if (!heredocs)
		return (NULL);
	while (++i < cmd_nb)
	{
		heredocs[i] = ft_lstnew(NULL);
		if (!heredocs[i])
			return (free_heredocs(heredocs));
	}
	heredocs[i] = NULL;
	return (heredocs);
}

static int	del_format_ok(char c)
{
	if (!ft_isalpha(c) && c != '$')
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
	else if (!del || !del_format_ok(del[0]))
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

static int	treat_chevron(t_list **begin_lexicon, t_list *lst,
							t_mini *mini, int index)
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
	{
		add_chevron(get_token(lst), get_token(lst->next), mini);
	}
	return (1);
}

void	process_chevrons(t_list **begin_lexicon, t_mini *mini)
{
	t_list	*lst;
	t_list	*prev_lst;
	char	*token;
	int		index;

	index = 0;
	lst = *begin_lexicon;
	prev_lst = NULL;
	while (lst)
	{
		token = get_token(lst);
		if (!ft_strncmp(token, "|\0", 2))
			index++;
		else if (ft_inbase(token[0], "<>"))
		{
			if (!treat_chevron(begin_lexicon, lst, mini, index))
			{
				ft_lstclear(begin_lexicon, &lst_del);
				return ;
			}
			remove_lst(begin_lexicon, lst->next, lst);
			remove_lst(begin_lexicon, lst, prev_lst);
		}
		prev_lst = lst;
		lst = lst->next;
	}
}
